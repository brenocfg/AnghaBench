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
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct ov2680_ctrls {TYPE_2__* auto_exp; TYPE_1__* auto_gain; } ;
struct ov2680_dev {int /*<<< orphan*/  is_streaming; int /*<<< orphan*/  is_enabled; struct ov2680_ctrls ctrls; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  V4L2_CID_AUTOGAIN 134 
#define  V4L2_CID_EXPOSURE 133 
#define  V4L2_CID_EXPOSURE_AUTO 132 
#define  V4L2_CID_GAIN 131 
#define  V4L2_CID_HFLIP 130 
#define  V4L2_CID_TEST_PATTERN 129 
#define  V4L2_CID_VFLIP 128 
 struct v4l2_subdev* ctrl_to_sd (struct v4l2_ctrl*) ; 
 int ov2680_exposure_set (struct ov2680_dev*,int) ; 
 int ov2680_gain_set (struct ov2680_dev*,int) ; 
 int ov2680_hflip_disable (struct ov2680_dev*) ; 
 int ov2680_hflip_enable (struct ov2680_dev*) ; 
 int ov2680_test_pattern_set (struct ov2680_dev*,int /*<<< orphan*/ ) ; 
 int ov2680_vflip_disable (struct ov2680_dev*) ; 
 int ov2680_vflip_enable (struct ov2680_dev*) ; 
 struct ov2680_dev* to_ov2680_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov2680_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = ctrl_to_sd(ctrl);
	struct ov2680_dev *sensor = to_ov2680_dev(sd);
	struct ov2680_ctrls *ctrls = &sensor->ctrls;

	if (!sensor->is_enabled)
		return 0;

	switch (ctrl->id) {
	case V4L2_CID_AUTOGAIN:
		return ov2680_gain_set(sensor, !!ctrl->val);
	case V4L2_CID_GAIN:
		return ov2680_gain_set(sensor, !!ctrls->auto_gain->val);
	case V4L2_CID_EXPOSURE_AUTO:
		return ov2680_exposure_set(sensor, !!ctrl->val);
	case V4L2_CID_EXPOSURE:
		return ov2680_exposure_set(sensor, !!ctrls->auto_exp->val);
	case V4L2_CID_VFLIP:
		if (sensor->is_streaming)
			return -EBUSY;
		if (ctrl->val)
			return ov2680_vflip_enable(sensor);
		else
			return ov2680_vflip_disable(sensor);
	case V4L2_CID_HFLIP:
		if (sensor->is_streaming)
			return -EBUSY;
		if (ctrl->val)
			return ov2680_hflip_enable(sensor);
		else
			return ov2680_hflip_disable(sensor);
	case V4L2_CID_TEST_PATTERN:
		return ov2680_test_pattern_set(sensor, ctrl->val);
	default:
		break;
	}

	return -EINVAL;
}