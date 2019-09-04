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
typedef  int u8 ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  cmatrix ;

/* Variables and functions */
 int* hsv_blue_x ; 
 int* hsv_blue_y ; 
 int* hsv_green_x ; 
 int* hsv_green_y ; 
 int* hsv_red_x ; 
 int* hsv_red_y ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void set_cmatrix(struct gspca_dev *gspca_dev,
		s32 brightness, s32 contrast, s32 satur, s32 hue)
{
	s32 hue_coord, hue_index = 180 + hue;
	u8 cmatrix[21];

	memset(cmatrix, 0, sizeof(cmatrix));
	cmatrix[2] = (contrast * 0x25 / 0x100) + 0x26;
	cmatrix[0] = 0x13 + (cmatrix[2] - 0x26) * 0x13 / 0x25;
	cmatrix[4] = 0x07 + (cmatrix[2] - 0x26) * 0x07 / 0x25;
	cmatrix[18] = brightness - 0x80;

	hue_coord = (hsv_red_x[hue_index] * satur) >> 8;
	cmatrix[6] = hue_coord;
	cmatrix[7] = (hue_coord >> 8) & 0x0f;

	hue_coord = (hsv_red_y[hue_index] * satur) >> 8;
	cmatrix[8] = hue_coord;
	cmatrix[9] = (hue_coord >> 8) & 0x0f;

	hue_coord = (hsv_green_x[hue_index] * satur) >> 8;
	cmatrix[10] = hue_coord;
	cmatrix[11] = (hue_coord >> 8) & 0x0f;

	hue_coord = (hsv_green_y[hue_index] * satur) >> 8;
	cmatrix[12] = hue_coord;
	cmatrix[13] = (hue_coord >> 8) & 0x0f;

	hue_coord = (hsv_blue_x[hue_index] * satur) >> 8;
	cmatrix[14] = hue_coord;
	cmatrix[15] = (hue_coord >> 8) & 0x0f;

	hue_coord = (hsv_blue_y[hue_index] * satur) >> 8;
	cmatrix[16] = hue_coord;
	cmatrix[17] = (hue_coord >> 8) & 0x0f;

	reg_w(gspca_dev, 0x10e1, cmatrix, 21);
}