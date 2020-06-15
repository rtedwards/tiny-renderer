#include "tgaimage.h"
#include <cmath>
using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int n = 4;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
	bool steep = false;
	if (abs(x0 - x1) < abs(y0 - y1))
	{ // If line is steep (>45) the image gets transposed
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}

	if (x0 > x1)
	{ // start line at left most x value
		swap(x0, x1);
		swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror = abs(dy) * 2;
	float error = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++)
	{
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0 * (1.0 - t) + y1 * t;

		if (steep)
		{
			image.set(y, x, color);
		}
		else
		{
			image.set(x, y, color);
		}
		error += derror;
		if (error > dx)
		{
			y += (y1 > y0 ? 1 : -1);
			error -= dx * 2;
		}
	}
}

int main(int argc, char **argv)
{
	TGAImage image(400, 400, TGAImage::RGB);
	// image.set(300, 400, red);
	line(13, 20, 80 * n, 40 * n, image, white);
	line(20, 13, 40 * n, 80 * n, image, red);
	line(80 * n, 40 * n, 13, 20, image, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}