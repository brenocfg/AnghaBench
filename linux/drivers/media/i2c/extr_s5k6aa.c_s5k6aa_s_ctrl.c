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
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int val; int /*<<< orphan*/  id; } ;
struct s5k6aa {scalar_t__ power; int /*<<< orphan*/  lock; TYPE_1__* preset; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_G_PREV_CFG_CHG ; 
 int /*<<< orphan*/  REG_P_COLORTEMP (int) ; 
 int /*<<< orphan*/  REG_USER_BRIGHTNESS ; 
 int /*<<< orphan*/  REG_USER_CONTRAST ; 
 int /*<<< orphan*/  REG_USER_SATURATION ; 
 int /*<<< orphan*/  REG_USER_SHARPBLUR ; 
#define  V4L2_CID_AUTO_WHITE_BALANCE 137 
#define  V4L2_CID_BRIGHTNESS 136 
#define  V4L2_CID_COLORFX 135 
#define  V4L2_CID_CONTRAST 134 
#define  V4L2_CID_EXPOSURE_AUTO 133 
#define  V4L2_CID_HFLIP 132 
#define  V4L2_CID_POWER_LINE_FREQUENCY 131 
#define  V4L2_CID_SATURATION 130 
#define  V4L2_CID_SHARPNESS 129 
#define  V4L2_CID_WHITE_BALANCE_TEMPERATURE 128 
 struct v4l2_subdev* ctrl_to_sd (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s5k6aa_set_anti_flicker (struct s5k6aa*,int) ; 
 int s5k6aa_set_auto_exposure (struct s5k6aa*,int) ; 
 int s5k6aa_set_awb (struct s5k6aa*,int) ; 
 int s5k6aa_set_colorfx (struct s5k6aa*,int) ; 
 int s5k6aa_set_mirror (struct s5k6aa*,int) ; 
 int s5k6aa_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct s5k6aa* to_s5k6aa (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k6aa_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = ctrl_to_sd(ctrl);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct s5k6aa *s5k6aa = to_s5k6aa(sd);
	int idx, err = 0;

	v4l2_dbg(1, debug, sd, "ctrl: 0x%x, value: %d\n", ctrl->id, ctrl->val);

	mutex_lock(&s5k6aa->lock);
	/*
	 * If the device is not powered up by the host driver do
	 * not apply any controls to H/W at this time. Instead
	 * the controls will be restored right after power-up.
	 */
	if (s5k6aa->power == 0)
		goto unlock;
	idx = s5k6aa->preset->index;

	switch (ctrl->id) {
	case V4L2_CID_AUTO_WHITE_BALANCE:
		err = s5k6aa_set_awb(s5k6aa, ctrl->val);
		break;

	case V4L2_CID_BRIGHTNESS:
		err = s5k6aa_write(client, REG_USER_BRIGHTNESS, ctrl->val);
		break;

	case V4L2_CID_COLORFX:
		err = s5k6aa_set_colorfx(s5k6aa, ctrl->val);
		break;

	case V4L2_CID_CONTRAST:
		err = s5k6aa_write(client, REG_USER_CONTRAST, ctrl->val);
		break;

	case V4L2_CID_EXPOSURE_AUTO:
		err = s5k6aa_set_auto_exposure(s5k6aa, ctrl->val);
		break;

	case V4L2_CID_HFLIP:
		err = s5k6aa_set_mirror(s5k6aa, ctrl->val);
		if (err)
			break;
		err = s5k6aa_write(client, REG_G_PREV_CFG_CHG, 1);
		break;

	case V4L2_CID_POWER_LINE_FREQUENCY:
		err = s5k6aa_set_anti_flicker(s5k6aa, ctrl->val);
		break;

	case V4L2_CID_SATURATION:
		err = s5k6aa_write(client, REG_USER_SATURATION, ctrl->val);
		break;

	case V4L2_CID_SHARPNESS:
		err = s5k6aa_write(client, REG_USER_SHARPBLUR, ctrl->val);
		break;

	case V4L2_CID_WHITE_BALANCE_TEMPERATURE:
		err = s5k6aa_write(client, REG_P_COLORTEMP(idx), ctrl->val);
		if (err)
			break;
		err = s5k6aa_write(client, REG_G_PREV_CFG_CHG, 1);
		break;
	}
unlock:
	mutex_unlock(&s5k6aa->lock);
	return err;
}