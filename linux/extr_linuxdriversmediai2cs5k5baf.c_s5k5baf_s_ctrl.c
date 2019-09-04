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
struct s5k5baf {scalar_t__ power; int /*<<< orphan*/  lock; int /*<<< orphan*/  apply_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_P_COLORTEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_USER_BRIGHTNESS ; 
 int /*<<< orphan*/  REG_USER_CONTRAST ; 
 int /*<<< orphan*/  REG_USER_SATURATION ; 
 int /*<<< orphan*/  REG_USER_SHARPBLUR ; 
#define  V4L2_CID_AUTO_WHITE_BALANCE 138 
#define  V4L2_CID_BRIGHTNESS 137 
#define  V4L2_CID_COLORFX 136 
#define  V4L2_CID_CONTRAST 135 
#define  V4L2_CID_EXPOSURE_AUTO 134 
#define  V4L2_CID_HFLIP 133 
#define  V4L2_CID_POWER_LINE_FREQUENCY 132 
#define  V4L2_CID_SATURATION 131 
#define  V4L2_CID_SHARPNESS 130 
#define  V4L2_CID_TEST_PATTERN 129 
#define  V4L2_CID_WHITE_BALANCE_TEMPERATURE 128 
 struct v4l2_subdev* ctrl_to_sd (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s5k5baf_clear_error (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_hw_set_anti_flicker (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_hw_set_auto_exposure (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_hw_set_awb (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_hw_set_colorfx (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_hw_set_mirror (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_hw_set_test_pattern (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_hw_sync_cfg (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_write (struct s5k5baf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct s5k5baf* to_s5k5baf (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k5baf_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = ctrl_to_sd(ctrl);
	struct s5k5baf *state = to_s5k5baf(sd);
	int ret;

	v4l2_dbg(1, debug, sd, "ctrl: %s, value: %d\n", ctrl->name, ctrl->val);

	mutex_lock(&state->lock);

	if (state->power == 0)
		goto unlock;

	switch (ctrl->id) {
	case V4L2_CID_AUTO_WHITE_BALANCE:
		s5k5baf_hw_set_awb(state, ctrl->val);
		break;

	case V4L2_CID_BRIGHTNESS:
		s5k5baf_write(state, REG_USER_BRIGHTNESS, ctrl->val);
		break;

	case V4L2_CID_COLORFX:
		s5k5baf_hw_set_colorfx(state, ctrl->val);
		break;

	case V4L2_CID_CONTRAST:
		s5k5baf_write(state, REG_USER_CONTRAST, ctrl->val);
		break;

	case V4L2_CID_EXPOSURE_AUTO:
		s5k5baf_hw_set_auto_exposure(state, ctrl->val);
		break;

	case V4L2_CID_HFLIP:
		s5k5baf_hw_set_mirror(state);
		break;

	case V4L2_CID_POWER_LINE_FREQUENCY:
		s5k5baf_hw_set_anti_flicker(state, ctrl->val);
		break;

	case V4L2_CID_SATURATION:
		s5k5baf_write(state, REG_USER_SATURATION, ctrl->val);
		break;

	case V4L2_CID_SHARPNESS:
		s5k5baf_write(state, REG_USER_SHARPBLUR, ctrl->val);
		break;

	case V4L2_CID_WHITE_BALANCE_TEMPERATURE:
		s5k5baf_write(state, REG_P_COLORTEMP(0), ctrl->val);
		if (state->apply_cfg)
			s5k5baf_hw_sync_cfg(state);
		break;

	case V4L2_CID_TEST_PATTERN:
		s5k5baf_hw_set_test_pattern(state, ctrl->val);
		break;
	}
unlock:
	ret = s5k5baf_clear_error(state);
	mutex_unlock(&state->lock);
	return ret;
}