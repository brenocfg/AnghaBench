#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {scalar_t__ bridge; scalar_t__ sensor; int /*<<< orphan*/  jpegqual; int /*<<< orphan*/  red; int /*<<< orphan*/  blue; int /*<<< orphan*/  quality; int /*<<< orphan*/  jpeg_hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct gspca_dev {int usb_err; int /*<<< orphan*/  exposure; int /*<<< orphan*/  autogain; int /*<<< orphan*/  gain; scalar_t__ curr_mode; TYPE_1__ pixfmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ BRIDGE_TP6800 ; 
 scalar_t__ BRIDGE_TP6810 ; 
 scalar_t__ SENSOR_CX0342 ; 
 scalar_t__ SENSOR_SOI763A ; 
 int /*<<< orphan*/  cx0342_6800_start (struct gspca_dev*) ; 
 int /*<<< orphan*/  cx0342_6810_start (struct gspca_dev*) ; 
 int /*<<< orphan*/  jpeg_define (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dqt (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setautogain (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setexposure (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setframerate (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setquality (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soi763a_6800_start (struct gspca_dev*) ; 
 int /*<<< orphan*/  soi763a_6810_start (struct gspca_dev*) ; 
 int /*<<< orphan*/  tp6810_late_start ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	jpeg_define(sd->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width);
	set_dqt(gspca_dev, sd->quality);
	if (sd->bridge == BRIDGE_TP6800) {
		if (sd->sensor == SENSOR_CX0342)
			cx0342_6800_start(gspca_dev);
		else
			soi763a_6800_start(gspca_dev);
	} else {
		if (sd->sensor == SENSOR_CX0342)
			cx0342_6810_start(gspca_dev);
		else
			soi763a_6810_start(gspca_dev);
		reg_w_buf(gspca_dev, tp6810_late_start,
				ARRAY_SIZE(tp6810_late_start));
		reg_w(gspca_dev, 0x80, 0x03);
		reg_w(gspca_dev, 0x82, gspca_dev->curr_mode ? 0x0a : 0x0e);

		if (sd->sensor == SENSOR_CX0342)
			setexposure(gspca_dev,
				v4l2_ctrl_g_ctrl(gspca_dev->exposure),
				v4l2_ctrl_g_ctrl(gspca_dev->gain),
				v4l2_ctrl_g_ctrl(sd->blue),
				v4l2_ctrl_g_ctrl(sd->red));
		else
			setexposure(gspca_dev,
				v4l2_ctrl_g_ctrl(gspca_dev->exposure),
				v4l2_ctrl_g_ctrl(gspca_dev->gain), 0, 0);
		if (sd->sensor == SENSOR_SOI763A)
			setquality(gspca_dev,
				   v4l2_ctrl_g_ctrl(sd->jpegqual));
		if (sd->bridge == BRIDGE_TP6810)
			setautogain(gspca_dev,
				    v4l2_ctrl_g_ctrl(gspca_dev->autogain));
	}

	setframerate(gspca_dev, v4l2_ctrl_g_ctrl(gspca_dev->exposure));

	return gspca_dev->usb_err;
}