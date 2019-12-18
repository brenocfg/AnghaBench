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
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {TYPE_2__ pixfmt; } ;
struct sd {scalar_t__ sensor; int sensor_width; int sensor_height; TYPE_3__ gspca_dev; TYPE_1__* freq; scalar_t__ sif; } ;
struct TYPE_4__ {int val; } ;

/* Variables and functions */
 int SC (int /*<<< orphan*/ ) ; 
 scalar_t__ SEN_OV7620 ; 
 int /*<<< orphan*/  reg_w (struct sd*,int,int) ; 

__attribute__((used)) static void w9968cf_set_crop_window(struct sd *sd)
{
	int start_cropx, start_cropy,  x, y, fw, fh, cw, ch,
	    max_width, max_height;

	if (sd->sif) {
		max_width  = 352;
		max_height = 288;
	} else {
		max_width  = 640;
		max_height = 480;
	}

	if (sd->sensor == SEN_OV7620) {
		/*
		 * Sigh, this is dependend on the clock / framerate changes
		 * made by the frequency control, sick.
		 *
		 * Note we cannot use v4l2_ctrl_g_ctrl here, as we get called
		 * from ov519.c:setfreq() with the ctrl lock held!
		 */
		if (sd->freq->val == 1) {
			start_cropx = 277;
			start_cropy = 37;
		} else {
			start_cropx = 105;
			start_cropy = 37;
		}
	} else {
		start_cropx = 320;
		start_cropy = 35;
	}

	/* Work around to avoid FP arithmetic */
	#define SC(x) ((x) << 10)

	/* Scaling factors */
	fw = SC(sd->gspca_dev.pixfmt.width) / max_width;
	fh = SC(sd->gspca_dev.pixfmt.height) / max_height;

	cw = (fw >= fh) ? max_width : SC(sd->gspca_dev.pixfmt.width) / fh;
	ch = (fw >= fh) ? SC(sd->gspca_dev.pixfmt.height) / fw : max_height;

	sd->sensor_width = max_width;
	sd->sensor_height = max_height;

	x = (max_width - cw) / 2;
	y = (max_height - ch) / 2;

	reg_w(sd, 0x10, start_cropx + x);
	reg_w(sd, 0x11, start_cropy + y);
	reg_w(sd, 0x12, start_cropx + x + cw);
	reg_w(sd, 0x13, start_cropy + y + ch);
}