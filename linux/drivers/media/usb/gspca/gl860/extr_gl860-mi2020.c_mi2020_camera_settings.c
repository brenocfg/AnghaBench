#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {size_t AC50Hz; size_t whitebal; size_t mirror; size_t flip; size_t brightness; size_t contrast; size_t gamma; size_t backlight; size_t sharpness; size_t hue; } ;
struct TYPE_6__ {size_t whitebal; size_t brightness; size_t contrast; size_t gamma; size_t backlight; size_t sharpness; } ;
struct TYPE_10__ {size_t backlight; size_t brightness; size_t sharpness; size_t contrast; size_t gamma; scalar_t__ hue; scalar_t__ mirror; scalar_t__ flip; scalar_t__ AC50Hz; size_t whitebal; } ;
struct sd {int mirrorMask; int nbIm; int waitSet; size_t swapRB; TYPE_2__ vold; TYPE_1__ vmax; TYPE_5__ vcur; } ;
struct TYPE_9__ {TYPE_3__* cam_mode; } ;
struct gspca_dev {scalar_t__ curr_mode; TYPE_4__ cam; } ;
typedef  size_t s32 ;
struct TYPE_8__ {size_t priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t IMAGE_640 ; 
 size_t IMAGE_800 ; 
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int,int,int*) ; 
 int* dat_bright1 ; 
 int* dat_bright3 ; 
 int* dat_bright4 ; 
 int* dat_bright5 ; 
 int* dat_bright6 ; 
 int* dat_freq1 ; 
 int* dat_hvflip1 ; 
 int* dat_hvflip3 ; 
 int* dat_hvflip5 ; 
 int* dat_hvflip6 ; 
 int* dat_multi5 ; 
 int* dat_multi6 ; 
 int* dat_wbal1 ; 
 int /*<<< orphan*/  fetch_idxdata (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  tbl_end_hvflip ; 
 int /*<<< orphan*/  tbl_init_post_alt_3B ; 
 int /*<<< orphan*/  tbl_middle_hvflip_big ; 
 int /*<<< orphan*/  tbl_middle_hvflip_low ; 

__attribute__((used)) static int mi2020_camera_settings(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	s32 reso = gspca_dev->cam.cam_mode[(s32) gspca_dev->curr_mode].priv;

	s32 backlight = sd->vcur.backlight;
	s32 bright =  sd->vcur.brightness;
	s32 sharp  =  sd->vcur.sharpness;
	s32 cntr   =  sd->vcur.contrast;
	s32 gam	   =  sd->vcur.gamma;
	s32 hue    = (sd->vcur.hue > 0);
	s32 mirror = (((sd->vcur.mirror > 0) ^ sd->mirrorMask) > 0);
	s32 flip   = (((sd->vcur.flip   > 0) ^ sd->mirrorMask) > 0);
	s32 freq   = (sd->vcur.AC50Hz > 0);
	s32 wbal   = sd->vcur.whitebal;

	u8 dat_sharp[] = {0x6c, 0x00, 0x08};
	u8 dat_bright2[] = {0x90, 0x00, 0x00};
	u8 dat_freq2[] = {0x90, 0x00, 0x80};
	u8 dat_multi1[] = {0x8c, 0xa7, 0x00};
	u8 dat_multi2[] = {0x90, 0x00, 0x00};
	u8 dat_multi3[] = {0x8c, 0xa7, 0x00};
	u8 dat_multi4[] = {0x90, 0x00, 0x00};
	u8 dat_hvflip2[] = {0x90, 0x04, 0x6c};
	u8 dat_hvflip4[] = {0x90, 0x00, 0x24};
	u8 dat_wbal2[] = {0x90, 0x00, 0x00};

	/* Less than 4 images received -> too early to set the settings */
	if (sd->nbIm < 4) {
		sd->waitSet = 1;
		return 0;
	}
	sd->waitSet = 0;

	if (freq != sd->vold.AC50Hz) {
		sd->vold.AC50Hz = freq;

		dat_freq2[2] = freq ? 0xc0 : 0x80;
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_freq1);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_freq2);
		msleep(20);
	}

	if (wbal != sd->vold.whitebal) {
		sd->vold.whitebal = wbal;
		if (wbal < 0 || wbal > sd->vmax.whitebal)
			wbal = 0;

		dat_multi1[2] = 0x9d;
		dat_multi3[2] = dat_multi1[2] + 1;
		if (wbal == 0) {
			dat_multi4[2] = dat_multi2[2] = 0;
			dat_wbal2[2] = 0x17;
		} else if (wbal == 1) {
			dat_multi4[2] = dat_multi2[2] = 0;
			dat_wbal2[2] = 0x35;
		} else if (wbal == 2) {
			dat_multi4[2] = dat_multi2[2] = 0x20;
			dat_wbal2[2] = 0x17;
		}
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi1);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi2);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi3);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi4);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_wbal1);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_wbal2);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi5);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi6);
	}

	if (mirror != sd->vold.mirror || flip != sd->vold.flip) {
		sd->vold.mirror = mirror;
		sd->vold.flip   = flip;

		dat_hvflip2[2] = 0x6c + 2 * (1 - flip) + (1 - mirror);
		dat_hvflip4[2] = 0x24 + 2 * (1 - flip) + (1 - mirror);

		fetch_idxdata(gspca_dev, tbl_init_post_alt_3B,
				ARRAY_SIZE(tbl_init_post_alt_3B));

		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip1);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip2);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip3);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip4);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip5);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip6);
		msleep(40);

		if (reso == IMAGE_640 || reso == IMAGE_800)
			fetch_idxdata(gspca_dev, tbl_middle_hvflip_low,
					ARRAY_SIZE(tbl_middle_hvflip_low));
		else
			fetch_idxdata(gspca_dev, tbl_middle_hvflip_big,
					ARRAY_SIZE(tbl_middle_hvflip_big));

		fetch_idxdata(gspca_dev, tbl_end_hvflip,
				ARRAY_SIZE(tbl_end_hvflip));
	}

	if (bright != sd->vold.brightness) {
		sd->vold.brightness = bright;
		if (bright < 0 || bright > sd->vmax.brightness)
			bright = 0;

		dat_bright2[2] = bright;
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_bright1);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_bright2);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_bright3);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_bright4);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_bright5);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_bright6);
	}

	if (cntr != sd->vold.contrast || gam != sd->vold.gamma) {
		sd->vold.contrast = cntr;
		if (cntr < 0 || cntr > sd->vmax.contrast)
			cntr = 0;
		sd->vold.gamma = gam;
		if (gam < 0 || gam > sd->vmax.gamma)
			gam = 0;

		dat_multi1[2] = 0x6d;
		dat_multi3[2] = dat_multi1[2] + 1;
		if (cntr == 0)
			cntr = 4;
		dat_multi4[2] = dat_multi2[2] = cntr * 0x10 + 2 - gam;
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi1);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi2);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi3);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi4);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi5);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi6);
	}

	if (backlight != sd->vold.backlight) {
		sd->vold.backlight = backlight;
		if (backlight < 0 || backlight > sd->vmax.backlight)
			backlight = 0;

		dat_multi1[2] = 0x9d;
		dat_multi3[2] = dat_multi1[2] + 1;
		dat_multi4[2] = dat_multi2[2] = backlight;
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi1);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi2);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi3);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi4);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi5);
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi6);
	}

	if (sharp != sd->vold.sharpness) {
		sd->vold.sharpness = sharp;
		if (sharp < 0 || sharp > sd->vmax.sharpness)
			sharp = 0;

		dat_sharp[1] = sharp;
		ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0032, 3, dat_sharp);
	}

	if (hue != sd->vold.hue) {
		sd->swapRB = hue;
		sd->vold.hue = hue;
	}

	return 0;
}