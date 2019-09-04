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
struct sd {int /*<<< orphan*/  illum_bottom; int /*<<< orphan*/  illum_top; } ;
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  setilluminators (struct gspca_dev*,int,int) ; 
 scalar_t__ v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (v4l2_ctrl_g_ctrl(sd->illum_top) ||
	    v4l2_ctrl_g_ctrl(sd->illum_bottom)) {
		setilluminators(gspca_dev, false, false);
		msleep(20);
	}

	gspca_dev->usb_buf[0] = 1;
	gspca_dev->usb_buf[1] = 0;
	reg_w(gspca_dev, 2);
}