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
struct v4l2_ctrl {int val; int id; } ;
struct adv7180_state {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int ADV7180_FLCONTROL_FL_ENABLE ; 
 int ADV7180_REG_BRI ; 
 int ADV7180_REG_CON ; 
 int ADV7180_REG_FLCONTROL ; 
 int ADV7180_REG_HUE ; 
 int ADV7180_REG_SD_SAT_CB ; 
 int ADV7180_REG_SD_SAT_CR ; 
 int EINVAL ; 
#define  V4L2_CID_ADV_FAST_SWITCH 132 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int adv7180_write (struct adv7180_state*,int,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* to_adv7180_sd (struct v4l2_ctrl*) ; 
 struct adv7180_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7180_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_adv7180_sd(ctrl);
	struct adv7180_state *state = to_state(sd);
	int ret = mutex_lock_interruptible(&state->mutex);
	int val;

	if (ret)
		return ret;
	val = ctrl->val;
	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		ret = adv7180_write(state, ADV7180_REG_BRI, val);
		break;
	case V4L2_CID_HUE:
		/*Hue is inverted according to HSL chart */
		ret = adv7180_write(state, ADV7180_REG_HUE, -val);
		break;
	case V4L2_CID_CONTRAST:
		ret = adv7180_write(state, ADV7180_REG_CON, val);
		break;
	case V4L2_CID_SATURATION:
		/*
		 *This could be V4L2_CID_BLUE_BALANCE/V4L2_CID_RED_BALANCE
		 *Let's not confuse the user, everybody understands saturation
		 */
		ret = adv7180_write(state, ADV7180_REG_SD_SAT_CB, val);
		if (ret < 0)
			break;
		ret = adv7180_write(state, ADV7180_REG_SD_SAT_CR, val);
		break;
	case V4L2_CID_ADV_FAST_SWITCH:
		if (ctrl->val) {
			/* ADI required write */
			adv7180_write(state, 0x80d9, 0x44);
			adv7180_write(state, ADV7180_REG_FLCONTROL,
				ADV7180_FLCONTROL_FL_ENABLE);
		} else {
			/* ADI required write */
			adv7180_write(state, 0x80d9, 0xc4);
			adv7180_write(state, ADV7180_REG_FLCONTROL, 0x00);
		}
		break;
	default:
		ret = -EINVAL;
	}

	mutex_unlock(&state->mutex);
	return ret;
}