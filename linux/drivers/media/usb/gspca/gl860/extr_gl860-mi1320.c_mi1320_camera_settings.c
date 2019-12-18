#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int whitebal; int brightness; int saturation; int sharpness; int hue; int backlight; int gamma; int contrast; } ;
struct TYPE_5__ {int AC50Hz; int whitebal; int brightness; int saturation; int sharpness; int hue; int backlight; int mirror; int flip; int gamma; int contrast; } ;
struct TYPE_4__ {int backlight; int brightness; int sharpness; int contrast; int gamma; int hue; int saturation; int whitebal; scalar_t__ mirror; scalar_t__ flip; scalar_t__ AC50Hz; } ;
struct sd {int mirrorMask; int swapRB; TYPE_3__ vmax; TYPE_2__ vold; TYPE_1__ vcur; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int,int,int*) ; 
 int* dat_hvflip1 ; 
 int* dat_wbalBL ; 
 int* dat_wbalLL ; 
 int* dat_wbalNL ; 
 int* tbl_backlight ; 
 int* tbl_bright ; 
 int* tbl_cntr1 ; 
 int* tbl_cntr2 ; 
 int* tbl_sat ; 

__attribute__((used)) static int mi1320_camera_settings(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	s32 backlight = sd->vcur.backlight;
	s32 bright = sd->vcur.brightness;
	s32 sharp  = sd->vcur.sharpness;
	s32 cntr   = sd->vcur.contrast;
	s32 gam	   = sd->vcur.gamma;
	s32 hue    = sd->vcur.hue;
	s32 sat	   = sd->vcur.saturation;
	s32 wbal   = sd->vcur.whitebal;
	s32 mirror = (((sd->vcur.mirror > 0) ^ sd->mirrorMask) > 0);
	s32 flip   = (((sd->vcur.flip   > 0) ^ sd->mirrorMask) > 0);
	s32 freq   = (sd->vcur.AC50Hz > 0);
	s32 i;

	if (freq != sd->vold.AC50Hz) {
		sd->vold.AC50Hz = freq;

		freq = 2 * (freq == 0);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00, 0x00f0, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba02, 0x00f1, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00       , 0x005b, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba01 + freq, 0x00f1, 0, NULL);
	}

	if (wbal != sd->vold.whitebal) {
		sd->vold.whitebal = wbal;
		if (wbal < 0 || wbal > sd->vmax.whitebal)
			wbal = 0;

		for (i = 0; i < 2; i++) {
			if (wbal == 0) { /* Normal light */
				ctrl_out(gspca_dev, 0x40, 1,
						0x0010, 0x0010, 0, NULL);
				ctrl_out(gspca_dev, 0x40, 1,
						0x0003, 0x00c1, 0, NULL);
				ctrl_out(gspca_dev, 0x40, 1,
						0x0042, 0x00c2, 0, NULL);
				ctrl_out(gspca_dev, 0x40, 3,
						0xba00, 0x0200, 48, dat_wbalNL);
			}

			if (wbal == 1) { /* Low light */
				ctrl_out(gspca_dev, 0x40, 1,
						0x0010, 0x0010, 0, NULL);
				ctrl_out(gspca_dev, 0x40, 1,
						0x0004, 0x00c1, 0, NULL);
				ctrl_out(gspca_dev, 0x40, 1,
						0x0043, 0x00c2, 0, NULL);
				ctrl_out(gspca_dev, 0x40, 3,
						0xba00, 0x0200, 48, dat_wbalLL);
			}

			if (wbal == 2) { /* Back light */
				ctrl_out(gspca_dev, 0x40, 1,
						0x0010, 0x0010, 0, NULL);
				ctrl_out(gspca_dev, 0x40, 1,
						0x0003, 0x00c1, 0, NULL);
				ctrl_out(gspca_dev, 0x40, 1,
						0x0042, 0x00c2, 0, NULL);
				ctrl_out(gspca_dev, 0x40, 3,
						0xba00, 0x0200, 44, dat_wbalBL);
			}
		}
	}

	if (bright != sd->vold.brightness) {
		sd->vold.brightness = bright;
		if (bright < 0 || bright > sd->vmax.brightness)
			bright = 0;

		bright = tbl_bright[bright];
		ctrl_out(gspca_dev, 0x40, 1, 0xba00, 0x00f0, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba01, 0x00f1, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00 + bright, 0x0034, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00 + bright, 0x00f1, 0, NULL);
	}

	if (sat != sd->vold.saturation) {
		sd->vold.saturation = sat;
		if (sat < 0 || sat > sd->vmax.saturation)
			sat = 0;

		sat = tbl_sat[sat];
		ctrl_out(gspca_dev, 0x40, 1, 0xba00, 0x00f0, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba01, 0x00f1, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00      , 0x0025, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00 + sat, 0x00f1, 0, NULL);
	}

	if (sharp != sd->vold.sharpness) {
		sd->vold.sharpness = sharp;
		if (sharp < 0 || sharp > sd->vmax.sharpness)
			sharp = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0xba00, 0x00f0, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba01, 0x00f1, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00        , 0x0005, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00 + sharp, 0x00f1, 0, NULL);
	}

	if (hue != sd->vold.hue) {
		/* 0=normal  1=NB  2="sepia"  3=negative  4=other  5=other2 */
		if (hue < 0 || hue > sd->vmax.hue)
			hue = 0;
		if (hue == sd->vmax.hue)
			sd->swapRB = 1;
		else
			sd->swapRB = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0xba00, 0x00f0, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba01, 0x00f1, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba70, 0x00e2, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00 + hue * (hue < 6), 0x00f1,
							0, NULL);
	}

	if (backlight != sd->vold.backlight) {
		sd->vold.backlight = backlight;
		if (backlight < 0 || backlight > sd->vmax.backlight)
			backlight = 0;

		backlight = tbl_backlight[backlight];
		for (i = 0; i < 2; i++) {
			ctrl_out(gspca_dev, 0x40, 1, 0xba00, 0x00f0, 0, NULL);
			ctrl_out(gspca_dev, 0x40, 1, 0xba01, 0x00f1, 0, NULL);
			ctrl_out(gspca_dev, 0x40, 1, 0xba74, 0x0006, 0, NULL);
			ctrl_out(gspca_dev, 0x40, 1, 0xba80 + backlight, 0x00f1,
								0, NULL);
		}
	}

	if (hue != sd->vold.hue) {
		sd->vold.hue = hue;

		ctrl_out(gspca_dev, 0x40, 1, 0xba00, 0x00f0, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba01, 0x00f1, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba70, 0x00e2, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00 + hue * (hue < 6), 0x00f1,
							0, NULL);
	}

	if (mirror != sd->vold.mirror || flip != sd->vold.flip) {
		u8 dat_hvflip2[4] = {0x20, 0x01, 0xf1, 0x00};
		sd->vold.mirror = mirror;
		sd->vold.flip = flip;

		dat_hvflip2[3] = flip + 2 * mirror;
		ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 4, dat_hvflip1);
		ctrl_out(gspca_dev, 0x40, 3, 0xba00, 0x0200, 4, dat_hvflip2);
	}

	if (gam != sd->vold.gamma) {
		sd->vold.gamma = gam;
		if (gam < 0 || gam > sd->vmax.gamma)
			gam = 0;

		gam = 2 * gam;
		ctrl_out(gspca_dev, 0x40, 1, 0xba00, 0x00f0, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba01, 0x00f1, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba04      , 0x003b, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba02 + gam, 0x00f1, 0, NULL);
	}

	if (cntr != sd->vold.contrast) {
		sd->vold.contrast = cntr;
		if (cntr < 0 || cntr > sd->vmax.contrast)
			cntr = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0xba00, 0x00f0, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba01, 0x00f1, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00 + tbl_cntr1[cntr], 0x0035,
							0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0xba00 + tbl_cntr2[cntr], 0x00f1,
							0, NULL);
	}

	return 0;
}