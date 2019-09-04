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
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; int /*<<< orphan*/  name; } ;
struct ov965x {scalar_t__ power; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUTOGAIN 136 
#define  V4L2_CID_AUTO_WHITE_BALANCE 135 
#define  V4L2_CID_BRIGHTNESS 134 
#define  V4L2_CID_EXPOSURE_AUTO 133 
#define  V4L2_CID_HFLIP 132 
#define  V4L2_CID_POWER_LINE_FREQUENCY 131 
#define  V4L2_CID_SATURATION 130 
#define  V4L2_CID_SHARPNESS 129 
#define  V4L2_CID_TEST_PATTERN 128 
 struct v4l2_subdev* ctrl_to_sd (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov965x_set_banding_filter (struct ov965x*,int /*<<< orphan*/ ) ; 
 int ov965x_set_brightness (struct ov965x*,int /*<<< orphan*/ ) ; 
 int ov965x_set_exposure (struct ov965x*,int /*<<< orphan*/ ) ; 
 int ov965x_set_flip (struct ov965x*) ; 
 int ov965x_set_gain (struct ov965x*,int /*<<< orphan*/ ) ; 
 int ov965x_set_saturation (struct ov965x*,int /*<<< orphan*/ ) ; 
 int ov965x_set_sharpness (struct ov965x*,int /*<<< orphan*/ ) ; 
 int ov965x_set_test_pattern (struct ov965x*,int /*<<< orphan*/ ) ; 
 int ov965x_set_white_balance (struct ov965x*,int /*<<< orphan*/ ) ; 
 struct ov965x* to_ov965x (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ov965x_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = ctrl_to_sd(ctrl);
	struct ov965x *ov965x = to_ov965x(sd);
	int ret = -EINVAL;

	v4l2_dbg(1, debug, sd, "s_ctrl: %s, value: %d. power: %d\n",
		 ctrl->name, ctrl->val, ov965x->power);

	mutex_lock(&ov965x->lock);
	/*
	 * If the device is not powered up now postpone applying control's
	 * value to the hardware, until it is ready to accept commands.
	 */
	if (ov965x->power == 0) {
		mutex_unlock(&ov965x->lock);
		return 0;
	}

	switch (ctrl->id) {
	case V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov965x_set_white_balance(ov965x, ctrl->val);
		break;

	case V4L2_CID_BRIGHTNESS:
		ret = ov965x_set_brightness(ov965x, ctrl->val);
		break;

	case V4L2_CID_EXPOSURE_AUTO:
		ret = ov965x_set_exposure(ov965x, ctrl->val);
		break;

	case V4L2_CID_AUTOGAIN:
		ret = ov965x_set_gain(ov965x, ctrl->val);
		break;

	case V4L2_CID_HFLIP:
		ret = ov965x_set_flip(ov965x);
		break;

	case V4L2_CID_POWER_LINE_FREQUENCY:
		ret = ov965x_set_banding_filter(ov965x, ctrl->val);
		break;

	case V4L2_CID_SATURATION:
		ret = ov965x_set_saturation(ov965x, ctrl->val);
		break;

	case V4L2_CID_SHARPNESS:
		ret = ov965x_set_sharpness(ov965x, ctrl->val);
		break;

	case V4L2_CID_TEST_PATTERN:
		ret = ov965x_set_test_pattern(ov965x, ctrl->val);
		break;
	}

	mutex_unlock(&ov965x->lock);
	return ret;
}