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
struct sd {void* brightness; } ;
struct TYPE_2__ {struct v4l2_ctrl_handler* ctrl_handler; } ;
struct gspca_dev {void* autogain; void* gain; void* exposure; TYPE_1__ vdev; struct v4l2_ctrl_handler ctrl_handler; } ;

/* Variables and functions */
 int PAC207_BRIGHTNESS_DEFAULT ; 
 int PAC207_BRIGHTNESS_MAX ; 
 int /*<<< orphan*/  PAC207_BRIGHTNESS_MIN ; 
 int PAC207_EXPOSURE_DEFAULT ; 
 int PAC207_EXPOSURE_MAX ; 
 int /*<<< orphan*/  PAC207_EXPOSURE_MIN ; 
 int PAC207_GAIN_DEFAULT ; 
 int PAC207_GAIN_MAX ; 
 int /*<<< orphan*/  PAC207_GAIN_MIN ; 
 int /*<<< orphan*/  V4L2_CID_AUTOGAIN ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sd_ctrl_ops ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (struct v4l2_ctrl_handler*,int) ; 
 void* v4l2_ctrl_new_std (struct v4l2_ctrl_handler*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int sd_init_controls(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct v4l2_ctrl_handler *hdl = &gspca_dev->ctrl_handler;

	gspca_dev->vdev.ctrl_handler = hdl;
	v4l2_ctrl_handler_init(hdl, 4);

	sd->brightness = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_BRIGHTNESS,
				PAC207_BRIGHTNESS_MIN, PAC207_BRIGHTNESS_MAX,
				1, PAC207_BRIGHTNESS_DEFAULT);
	gspca_dev->autogain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	gspca_dev->exposure = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_EXPOSURE,
				PAC207_EXPOSURE_MIN, PAC207_EXPOSURE_MAX,
				1, PAC207_EXPOSURE_DEFAULT);
	gspca_dev->gain = v4l2_ctrl_new_std(hdl, &sd_ctrl_ops,
				V4L2_CID_GAIN,
				PAC207_GAIN_MIN, PAC207_GAIN_MAX,
				1, PAC207_GAIN_DEFAULT);
	if (hdl->error) {
		pr_err("Could not initialize controls\n");
		return hdl->error;
	}
	v4l2_ctrl_auto_cluster(3, &gspca_dev->autogain, 0, false);
	return 0;
}