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
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct ov5640_dev {scalar_t__ power_count; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUTOGAIN 137 
#define  V4L2_CID_AUTO_WHITE_BALANCE 136 
#define  V4L2_CID_CONTRAST 135 
#define  V4L2_CID_EXPOSURE_AUTO 134 
#define  V4L2_CID_HFLIP 133 
#define  V4L2_CID_HUE 132 
#define  V4L2_CID_POWER_LINE_FREQUENCY 131 
#define  V4L2_CID_SATURATION 130 
#define  V4L2_CID_TEST_PATTERN 129 
#define  V4L2_CID_VFLIP 128 
 struct v4l2_subdev* ctrl_to_sd (struct v4l2_ctrl*) ; 
 int ov5640_set_ctrl_contrast (struct ov5640_dev*,int /*<<< orphan*/ ) ; 
 int ov5640_set_ctrl_exposure (struct ov5640_dev*,int /*<<< orphan*/ ) ; 
 int ov5640_set_ctrl_gain (struct ov5640_dev*,int /*<<< orphan*/ ) ; 
 int ov5640_set_ctrl_hflip (struct ov5640_dev*,int /*<<< orphan*/ ) ; 
 int ov5640_set_ctrl_hue (struct ov5640_dev*,int /*<<< orphan*/ ) ; 
 int ov5640_set_ctrl_light_freq (struct ov5640_dev*,int /*<<< orphan*/ ) ; 
 int ov5640_set_ctrl_saturation (struct ov5640_dev*,int /*<<< orphan*/ ) ; 
 int ov5640_set_ctrl_test_pattern (struct ov5640_dev*,int /*<<< orphan*/ ) ; 
 int ov5640_set_ctrl_vflip (struct ov5640_dev*,int /*<<< orphan*/ ) ; 
 int ov5640_set_ctrl_white_balance (struct ov5640_dev*,int /*<<< orphan*/ ) ; 
 struct ov5640_dev* to_ov5640_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov5640_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = ctrl_to_sd(ctrl);
	struct ov5640_dev *sensor = to_ov5640_dev(sd);
	int ret;

	/* v4l2_ctrl_lock() locks our own mutex */

	/*
	 * If the device is not powered up by the host driver do
	 * not apply any controls to H/W at this time. Instead
	 * the controls will be restored right after power-up.
	 */
	if (sensor->power_count == 0)
		return 0;

	switch (ctrl->id) {
	case V4L2_CID_AUTOGAIN:
		ret = ov5640_set_ctrl_gain(sensor, ctrl->val);
		break;
	case V4L2_CID_EXPOSURE_AUTO:
		ret = ov5640_set_ctrl_exposure(sensor, ctrl->val);
		break;
	case V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov5640_set_ctrl_white_balance(sensor, ctrl->val);
		break;
	case V4L2_CID_HUE:
		ret = ov5640_set_ctrl_hue(sensor, ctrl->val);
		break;
	case V4L2_CID_CONTRAST:
		ret = ov5640_set_ctrl_contrast(sensor, ctrl->val);
		break;
	case V4L2_CID_SATURATION:
		ret = ov5640_set_ctrl_saturation(sensor, ctrl->val);
		break;
	case V4L2_CID_TEST_PATTERN:
		ret = ov5640_set_ctrl_test_pattern(sensor, ctrl->val);
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY:
		ret = ov5640_set_ctrl_light_freq(sensor, ctrl->val);
		break;
	case V4L2_CID_HFLIP:
		ret = ov5640_set_ctrl_hflip(sensor, ctrl->val);
		break;
	case V4L2_CID_VFLIP:
		ret = ov5640_set_ctrl_vflip(sensor, ctrl->val);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}