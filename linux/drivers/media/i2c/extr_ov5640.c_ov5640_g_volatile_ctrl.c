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
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; } ;
struct TYPE_5__ {TYPE_3__* exposure; TYPE_1__* gain; } ;
struct ov5640_dev {TYPE_2__ ctrls; } ;
struct TYPE_6__ {int val; } ;
struct TYPE_4__ {int val; } ;

/* Variables and functions */
#define  V4L2_CID_AUTOGAIN 129 
#define  V4L2_CID_EXPOSURE_AUTO 128 
 struct v4l2_subdev* ctrl_to_sd (struct v4l2_ctrl*) ; 
 int ov5640_get_exposure (struct ov5640_dev*) ; 
 int ov5640_get_gain (struct ov5640_dev*) ; 
 struct ov5640_dev* to_ov5640_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov5640_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = ctrl_to_sd(ctrl);
	struct ov5640_dev *sensor = to_ov5640_dev(sd);
	int val;

	/* v4l2_ctrl_lock() locks our own mutex */

	switch (ctrl->id) {
	case V4L2_CID_AUTOGAIN:
		val = ov5640_get_gain(sensor);
		if (val < 0)
			return val;
		sensor->ctrls.gain->val = val;
		break;
	case V4L2_CID_EXPOSURE_AUTO:
		val = ov5640_get_exposure(sensor);
		if (val < 0)
			return val;
		sensor->ctrls.exposure->val = val;
		break;
	}

	return 0;
}