#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl_handler {int error; } ;
struct TYPE_3__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct TYPE_4__ {TYPE_1__ vdev; struct v4l2_ctrl_handler ctrl_handler; } ;
struct sd {void* hflip; void* autoexpo; void* auto_white_bal; void* vflip; void* gain; void* expo; void* blue_bal; void* red_bal; int /*<<< orphan*/  green_bal; TYPE_2__ gspca_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PO1030_BLUE_GAIN_DEFAULT ; 
 int /*<<< orphan*/  PO1030_EXPOSURE_DEFAULT ; 
 int /*<<< orphan*/  PO1030_GLOBAL_GAIN_DEFAULT ; 
 int /*<<< orphan*/  PO1030_RED_GAIN_DEFAULT ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_BLUE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_RED_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_MANUAL ; 
 int /*<<< orphan*/  po1030_ctrl_ops ; 
 int /*<<< orphan*/  po1030_greenbal_cfg ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_custom (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 void* v4l2_ctrl_new_std_menu (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int po1030_init_controls(struct sd *sd)
{
	struct v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	sd->gspca_dev.vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 9);

	sd->auto_white_bal = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops,
					       V4L2_CID_AUTO_WHITE_BALANCE,
					       0, 1, 1, 0);
	sd->green_bal = v4l2_ctrl_new_custom(hdl, &po1030_greenbal_cfg, NULL);
	sd->red_bal = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops,
					V4L2_CID_RED_BALANCE, 0, 255, 1,
					PO1030_RED_GAIN_DEFAULT);
	sd->blue_bal = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops,
					V4L2_CID_BLUE_BALANCE, 0, 255, 1,
					PO1030_BLUE_GAIN_DEFAULT);

	sd->autoexpo = v4l2_ctrl_new_std_menu(hdl, &po1030_ctrl_ops,
			  V4L2_CID_EXPOSURE_AUTO, 1, 0, V4L2_EXPOSURE_MANUAL);
	sd->expo = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops, V4L2_CID_EXPOSURE,
			  0, 0x2ff, 1, PO1030_EXPOSURE_DEFAULT);

	sd->gain = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops, V4L2_CID_GAIN, 0,
				     0x4f, 1, PO1030_GLOBAL_GAIN_DEFAULT);

	sd->hflip = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops, V4L2_CID_HFLIP,
				      0, 1, 1, 0);
	sd->vflip = v4l2_ctrl_new_std(hdl, &po1030_ctrl_ops, V4L2_CID_VFLIP,
				      0, 1, 1, 0);

	if (hdl->error) {
		pr_err("Could not initialize controls\n");
		return hdl->error;
	}

	v4l2_ctrl_auto_cluster(4, &sd->auto_white_bal, 0, false);
	v4l2_ctrl_auto_cluster(2, &sd->autoexpo, 0, false);
	v4l2_ctrl_cluster(2, &sd->hflip);

	return 0;
}