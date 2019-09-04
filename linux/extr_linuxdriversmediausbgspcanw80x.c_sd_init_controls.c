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
struct v4l2_ctrl_handler {int error; } ;
struct sd {int webcam; } ;
struct TYPE_2__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct gspca_dev {void* autogain; void* exposure; void* gain; TYPE_1__ vdev; struct v4l2_ctrl_handler ctrl_handler; } ;

/* Variables and functions */
#define  Cvideopro 132 
#define  DvcV6 131 
#define  Kr651us 130 
#define  Kritter 129 
#define  P35u 128 
 int /*<<< orphan*/  V4L2_CID_AUTOGAIN ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sd_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int sd_init_controls(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *)gspca_dev;
	struct v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 3);
	switch (sd->webcam) {
	case P35u:
		gspca_dev->autogain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
		/* For P35u choose coarse expo auto gain function gain minimum,
		 * to avoid a large settings jump the first auto adjustment */
		gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0, 127, 1, 127 / 5 * 2);
		gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 9, 1, 9);
		break;
	case Kr651us:
		gspca_dev->autogain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
		gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_GAIN, 0, 253, 1, 128);
		/* fall through */
	case Cvideopro:
	case DvcV6:
	case Kritter:
		gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 315, 1, 150);
		break;
	default:
		break;
	}

	if (hdl->error) {
		pr_err("Could not initialize controls\n");
		return hdl->error;
	}
	if (gspca_dev->autogain)
		v4l2_ctrl_auto_cluster(3, &gspca_dev->autogain, 0, false);
	return 0;
}