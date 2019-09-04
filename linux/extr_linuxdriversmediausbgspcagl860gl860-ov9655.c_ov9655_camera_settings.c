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
typedef  char u8 ;
struct TYPE_6__ {scalar_t__ brightness; scalar_t__ hue; } ;
struct TYPE_5__ {scalar_t__ brightness; } ;
struct TYPE_4__ {scalar_t__ brightness; scalar_t__ hue; } ;
struct sd {int swapRB; TYPE_3__ vold; TYPE_2__ vmax; TYPE_1__ vcur; } ;
struct gspca_dev {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_out (struct gspca_dev*,int,int,int,int,int,char*) ; 

__attribute__((used)) static int ov9655_camera_settings(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	u8 dat_bright[] = "\x04\x00\x10\x7c\xa1\x00\x00\x70";

	s32 bright = sd->vcur.brightness;
	s32 hue    = sd->vcur.hue;

	if (bright != sd->vold.brightness) {
		sd->vold.brightness = bright;
		if (bright < 0 || bright > sd->vmax.brightness)
			bright = 0;

		dat_bright[3] = bright;
		ctrl_out(gspca_dev, 0x40, 3, 0x6000, 0x0200, 8, dat_bright);
	}

	if (hue != sd->vold.hue) {
		sd->vold.hue = hue;
		sd->swapRB = (hue != 0);
	}

	return 0;
}