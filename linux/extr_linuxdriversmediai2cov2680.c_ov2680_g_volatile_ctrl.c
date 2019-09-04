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
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; } ;
struct ov2680_ctrls {TYPE_2__* exposure; TYPE_1__* gain; } ;
struct ov2680_dev {int /*<<< orphan*/  is_enabled; struct ov2680_ctrls ctrls; } ;
struct TYPE_4__ {int val; } ;
struct TYPE_3__ {int val; } ;

/* Variables and functions */
#define  V4L2_CID_EXPOSURE 129 
#define  V4L2_CID_GAIN 128 
 struct v4l2_subdev* ctrl_to_sd (struct v4l2_ctrl*) ; 
 int ov2680_exposure_get (struct ov2680_dev*) ; 
 int ov2680_gain_get (struct ov2680_dev*) ; 
 struct ov2680_dev* to_ov2680_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov2680_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = ctrl_to_sd(ctrl);
	struct ov2680_dev *sensor = to_ov2680_dev(sd);
	struct ov2680_ctrls *ctrls = &sensor->ctrls;
	int val;

	if (!sensor->is_enabled)
		return 0;

	switch (ctrl->id) {
	case V4L2_CID_GAIN:
		val = ov2680_gain_get(sensor);
		if (val < 0)
			return val;
		ctrls->gain->val = val;
		break;
	case V4L2_CID_EXPOSURE:
		val = ov2680_exposure_get(sensor);
		if (val < 0)
			return val;
		ctrls->exposure->val = val;
		break;
	}

	return 0;
}