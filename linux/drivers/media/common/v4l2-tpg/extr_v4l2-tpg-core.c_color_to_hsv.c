#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tpg_data {scalar_t__ real_hsv_enc; } ;

/* Variables and functions */
 scalar_t__ V4L2_HSV_ENC_180 ; 
 int max3 (int,int,int) ; 
 int min3 (int,int,int) ; 

__attribute__((used)) static void color_to_hsv(struct tpg_data *tpg, int r, int g, int b,
			   int *h, int *s, int *v)
{
	int max_rgb, min_rgb, diff_rgb;
	int aux;
	int third;
	int third_size;

	r >>= 4;
	g >>= 4;
	b >>= 4;

	/* Value */
	max_rgb = max3(r, g, b);
	*v = max_rgb;
	if (!max_rgb) {
		*h = 0;
		*s = 0;
		return;
	}

	/* Saturation */
	min_rgb = min3(r, g, b);
	diff_rgb = max_rgb - min_rgb;
	aux = 255 * diff_rgb;
	aux += max_rgb / 2;
	aux /= max_rgb;
	*s = aux;
	if (!aux) {
		*h = 0;
		return;
	}

	third_size = (tpg->real_hsv_enc == V4L2_HSV_ENC_180) ? 60 : 85;

	/* Hue */
	if (max_rgb == r) {
		aux =  g - b;
		third = 0;
	} else if (max_rgb == g) {
		aux =  b - r;
		third = third_size;
	} else {
		aux =  r - g;
		third = third_size * 2;
	}

	aux *= third_size / 2;
	aux += diff_rgb / 2;
	aux /= diff_rgb;
	aux += third;

	/* Clamp Hue */
	if (tpg->real_hsv_enc == V4L2_HSV_ENC_180) {
		if (aux < 0)
			aux += 180;
		else if (aux > 180)
			aux -= 180;
	} else {
		aux = aux & 0xff;
	}

	*h = aux;
}