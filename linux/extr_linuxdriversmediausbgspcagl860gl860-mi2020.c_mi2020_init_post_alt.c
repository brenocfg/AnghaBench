#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {size_t mirror; size_t flip; size_t AC50Hz; size_t whitebal; } ;
struct TYPE_8__ {scalar_t__ mirror; scalar_t__ flip; scalar_t__ AC50Hz; size_t whitebal; } ;
struct sd {int mirrorMask; int nbIm; TYPE_1__ vold; TYPE_4__ vcur; } ;
struct TYPE_7__ {TYPE_2__* cam_mode; } ;
struct gspca_dev {scalar_t__ curr_mode; TYPE_3__ cam; } ;
typedef  size_t s32 ;
struct TYPE_6__ {size_t priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  IMAGE_1280 131 
#define  IMAGE_1600 130 
#define  IMAGE_640 129 
#define  IMAGE_800 128 
 int /*<<< orphan*/  common (struct gspca_dev*) ; 
 int /*<<< orphan*/  ctrl_in (struct gspca_dev*,int,int,int,int,int,int*) ; 
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int,int,...) ; 
 int* dat_1280 ; 
 int* dat_1600 ; 
 int* dat_640 ; 
 int* dat_800 ; 
 int* dat_freq1 ; 
 int* dat_hvflip1 ; 
 int* dat_hvflip3 ; 
 int* dat_hvflip5 ; 
 int* dat_hvflip6 ; 
 int* dat_multi5 ; 
 int* dat_multi6 ; 
 int* dat_wbal1 ; 
 int /*<<< orphan*/  fetch_idxdata (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi2020_camera_settings (struct gspca_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  tbl_end_hvflip ; 
 int /*<<< orphan*/  tbl_init_post_alt_3B ; 
 int /*<<< orphan*/  tbl_init_post_alt_big ; 
 int /*<<< orphan*/  tbl_init_post_alt_low1 ; 
 int /*<<< orphan*/  tbl_init_post_alt_low2 ; 
 int /*<<< orphan*/  tbl_init_post_alt_low3 ; 
 int /*<<< orphan*/  tbl_middle_hvflip_big ; 
 int /*<<< orphan*/  tbl_middle_hvflip_low ; 

__attribute__((used)) static int mi2020_init_post_alt(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	s32 reso = gspca_dev->cam.cam_mode[(s32) gspca_dev->curr_mode].priv;

	s32 mirror = (((sd->vcur.mirror > 0) ^ sd->mirrorMask) > 0);
	s32 flip   = (((sd->vcur.flip   > 0) ^ sd->mirrorMask) > 0);
	s32 freq   = (sd->vcur.AC50Hz  > 0);
	s32 wbal   = sd->vcur.whitebal;

	u8 dat_freq2[] = {0x90, 0x00, 0x80};
	u8 dat_multi1[] = {0x8c, 0xa7, 0x00};
	u8 dat_multi2[] = {0x90, 0x00, 0x00};
	u8 dat_multi3[] = {0x8c, 0xa7, 0x00};
	u8 dat_multi4[] = {0x90, 0x00, 0x00};
	u8 dat_hvflip2[] = {0x90, 0x04, 0x6c};
	u8 dat_hvflip4[] = {0x90, 0x00, 0x24};
	u8 dat_wbal2[] = {0x90, 0x00, 0x00};
	u8 c;

	sd->nbIm = -1;

	dat_freq2[2] = freq ? 0xc0 : 0x80;
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
	dat_hvflip2[2] = 0x6c + 2 * (1 - flip) + (1 - mirror);
	dat_hvflip4[2] = 0x24 + 2 * (1 - flip) + (1 - mirror);

	msleep(200);
	ctrl_out(gspca_dev, 0x40, 5, 0x0001, 0x0000, 0, NULL);
	msleep(2);

	common(gspca_dev);

	msleep(142);
	ctrl_out(gspca_dev, 0x40,  1, 0x0010, 0x0010,  0, NULL);
	ctrl_out(gspca_dev, 0x40,  1, 0x0003, 0x00c1,  0, NULL);
	ctrl_out(gspca_dev, 0x40,  1, 0x0042, 0x00c2,  0, NULL);
	ctrl_out(gspca_dev, 0x40,  1, 0x006a, 0x000d,  0, NULL);

	switch (reso) {
	case IMAGE_640:
	case IMAGE_800:
		if (reso != IMAGE_800)
			ctrl_out(gspca_dev, 0x40,  3, 0x0000, 0x0200,
				12, dat_640);
		else
			ctrl_out(gspca_dev, 0x40,  3, 0x0000, 0x0200,
				12, dat_800);

		fetch_idxdata(gspca_dev, tbl_init_post_alt_low1,
					ARRAY_SIZE(tbl_init_post_alt_low1));

		if (reso == IMAGE_800)
			fetch_idxdata(gspca_dev, tbl_init_post_alt_low2,
					ARRAY_SIZE(tbl_init_post_alt_low2));

		fetch_idxdata(gspca_dev, tbl_init_post_alt_low3,
				ARRAY_SIZE(tbl_init_post_alt_low3));

		ctrl_out(gspca_dev, 0x40, 1, 0x0010, 0x0010, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x0000, 0x00c1, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x0041, 0x00c2, 0, NULL);
		msleep(120);
		break;

	case IMAGE_1280:
	case IMAGE_1600:
		if (reso == IMAGE_1280) {
			ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200,
					12, dat_1280);
			ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033,
					3, "\x8c\x27\x07");
			ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033,
					3, "\x90\x05\x04");
			ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033,
					3, "\x8c\x27\x09");
			ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033,
					3, "\x90\x04\x02");
		} else {
			ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200,
					12, dat_1600);
			ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033,
					3, "\x8c\x27\x07");
			ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033,
					3, "\x90\x06\x40");
			ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033,
					3, "\x8c\x27\x09");
			ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033,
					3, "\x90\x04\xb0");
		}

		fetch_idxdata(gspca_dev, tbl_init_post_alt_big,
				ARRAY_SIZE(tbl_init_post_alt_big));

		ctrl_out(gspca_dev, 0x40, 1, 0x0001, 0x0010, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x0000, 0x00c1, 0, NULL);
		ctrl_out(gspca_dev, 0x40, 1, 0x0041, 0x00c2, 0, NULL);
		msleep(1850);
	}

	ctrl_out(gspca_dev, 0x40, 1, 0x0040, 0x0000, 0, NULL);
	msleep(40);

	/* AC power frequency */
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_freq1);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_freq2);
	msleep(33);
	/* light source */
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi1);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi2);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi3);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi4);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_wbal1);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_wbal2);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi5);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_multi6);
	msleep(7);
	ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0000, 1, &c);

	fetch_idxdata(gspca_dev, tbl_init_post_alt_3B,
			ARRAY_SIZE(tbl_init_post_alt_3B));

	/* hvflip */
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip1);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip2);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip3);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip4);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip5);
	ctrl_out(gspca_dev, 0x40, 3, 0x7a00, 0x0033, 3, dat_hvflip6);
	msleep(250);

	if (reso == IMAGE_640 || reso == IMAGE_800)
		fetch_idxdata(gspca_dev, tbl_middle_hvflip_low,
				ARRAY_SIZE(tbl_middle_hvflip_low));
	else
		fetch_idxdata(gspca_dev, tbl_middle_hvflip_big,
				ARRAY_SIZE(tbl_middle_hvflip_big));

	fetch_idxdata(gspca_dev, tbl_end_hvflip,
			ARRAY_SIZE(tbl_end_hvflip));

	sd->nbIm = 0;

	sd->vold.mirror    = mirror;
	sd->vold.flip      = flip;
	sd->vold.AC50Hz    = freq;
	sd->vold.whitebal  = wbal;

	mi2020_camera_settings(gspca_dev);

	return 0;
}