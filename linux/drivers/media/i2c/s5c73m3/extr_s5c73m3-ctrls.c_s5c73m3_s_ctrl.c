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
struct v4l2_ctrl {int val; int flags; int id; int /*<<< orphan*/  name; } ;
struct s5c73m3 {scalar_t__ power; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMM_WDR ; 
 int /*<<< orphan*/  COMM_ZOOM_STEP ; 
 int EINVAL ; 
#define  V4L2_CID_3A_LOCK 142 
#define  V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE 141 
#define  V4L2_CID_COLORFX 140 
#define  V4L2_CID_CONTRAST 139 
#define  V4L2_CID_EXPOSURE_AUTO 138 
#define  V4L2_CID_FOCUS_AUTO 137 
#define  V4L2_CID_IMAGE_STABILIZATION 136 
#define  V4L2_CID_ISO_SENSITIVITY 135 
#define  V4L2_CID_JPEG_COMPRESSION_QUALITY 134 
#define  V4L2_CID_POWER_LINE_FREQUENCY 133 
#define  V4L2_CID_SATURATION 132 
#define  V4L2_CID_SCENE_MODE 131 
#define  V4L2_CID_SHARPNESS 130 
#define  V4L2_CID_WIDE_DYNAMIC_RANGE 129 
#define  V4L2_CID_ZOOM_ABSOLUTE 128 
 int V4L2_CTRL_FLAG_INACTIVE ; 
 struct v4l2_subdev* ctrl_to_sensor_sd (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s5c73m3_3a_lock (struct s5c73m3*,struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  s5c73m3_dbg ; 
 int s5c73m3_isp_command (struct s5c73m3*,int /*<<< orphan*/ ,int) ; 
 int s5c73m3_set_auto_focus (struct s5c73m3*,int) ; 
 int s5c73m3_set_colorfx (struct s5c73m3*,int) ; 
 int s5c73m3_set_contrast (struct s5c73m3*,int) ; 
 int s5c73m3_set_exposure (struct s5c73m3*,int) ; 
 int s5c73m3_set_iso (struct s5c73m3*,int) ; 
 int s5c73m3_set_jpeg_quality (struct s5c73m3*,int) ; 
 int s5c73m3_set_power_line_freq (struct s5c73m3*,int) ; 
 int s5c73m3_set_saturation (struct s5c73m3*,int) ; 
 int s5c73m3_set_scene_program (struct s5c73m3*,int) ; 
 int s5c73m3_set_sharpness (struct s5c73m3*,int) ; 
 int s5c73m3_set_stabilization (struct s5c73m3*,int) ; 
 int s5c73m3_set_white_balance (struct s5c73m3*,int) ; 
 struct s5c73m3* sensor_sd_to_s5c73m3 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int s5c73m3_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = ctrl_to_sensor_sd(ctrl);
	struct s5c73m3 *state = sensor_sd_to_s5c73m3(sd);
	int ret = 0;

	v4l2_dbg(1, s5c73m3_dbg, sd, "set_ctrl: %s, value: %d\n",
		 ctrl->name, ctrl->val);

	mutex_lock(&state->lock);
	/*
	 * If the device is not powered up by the host driver do
	 * not apply any controls to H/W at this time. Instead
	 * the controls will be restored right after power-up.
	 */
	if (state->power == 0)
		goto unlock;

	if (ctrl->flags & V4L2_CTRL_FLAG_INACTIVE) {
		ret = -EINVAL;
		goto unlock;
	}

	switch (ctrl->id) {
	case V4L2_CID_3A_LOCK:
		ret = s5c73m3_3a_lock(state, ctrl);
		break;

	case V4L2_CID_AUTO_N_PRESET_WHITE_BALANCE:
		ret = s5c73m3_set_white_balance(state, ctrl->val);
		break;

	case V4L2_CID_CONTRAST:
		ret = s5c73m3_set_contrast(state, ctrl->val);
		break;

	case V4L2_CID_COLORFX:
		ret = s5c73m3_set_colorfx(state, ctrl->val);
		break;

	case V4L2_CID_EXPOSURE_AUTO:
		ret = s5c73m3_set_exposure(state, ctrl->val);
		break;

	case V4L2_CID_FOCUS_AUTO:
		ret = s5c73m3_set_auto_focus(state, ctrl->val);
		break;

	case V4L2_CID_IMAGE_STABILIZATION:
		ret = s5c73m3_set_stabilization(state, ctrl->val);
		break;

	case V4L2_CID_ISO_SENSITIVITY:
		ret = s5c73m3_set_iso(state, ctrl->val);
		break;

	case V4L2_CID_JPEG_COMPRESSION_QUALITY:
		ret = s5c73m3_set_jpeg_quality(state, ctrl->val);
		break;

	case V4L2_CID_POWER_LINE_FREQUENCY:
		ret = s5c73m3_set_power_line_freq(state, ctrl->val);
		break;

	case V4L2_CID_SATURATION:
		ret = s5c73m3_set_saturation(state, ctrl->val);
		break;

	case V4L2_CID_SCENE_MODE:
		ret = s5c73m3_set_scene_program(state, ctrl->val);
		break;

	case V4L2_CID_SHARPNESS:
		ret = s5c73m3_set_sharpness(state, ctrl->val);
		break;

	case V4L2_CID_WIDE_DYNAMIC_RANGE:
		ret = s5c73m3_isp_command(state, COMM_WDR, !!ctrl->val);
		break;

	case V4L2_CID_ZOOM_ABSOLUTE:
		ret = s5c73m3_isp_command(state, COMM_ZOOM_STEP, ctrl->val);
		break;
	}
unlock:
	mutex_unlock(&state->lock);
	return ret;
}