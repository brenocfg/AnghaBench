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
typedef  int u32 ;
struct vchiq_mmal_port {int dummy; } ;
struct v4l2_ctrl {int val; } ;
struct bm2835_mmal_v4l2_ctrl {scalar_t__ mmal_id; scalar_t__ id; } ;
struct bm2835_mmal_dev {int exposure_mode_user; int manual_shutter_speed; int exposure_mode_v4l2_user; int exp_auto_priority; scalar_t__ scene_mode; int exposure_mode_active; int /*<<< orphan*/  instance; TYPE_1__** component; } ;
typedef  int /*<<< orphan*/  shutter_speed ;
typedef  enum mmal_parameter_exposuremode { ____Placeholder_mmal_parameter_exposuremode } mmal_parameter_exposuremode ;
struct TYPE_2__ {struct vchiq_mmal_port control; } ;

/* Variables and functions */
 size_t COMP_CAMERA ; 
 scalar_t__ MMAL_PARAMETER_EXPOSURE_MODE ; 
 scalar_t__ MMAL_PARAMETER_SHUTTER_SPEED ; 
 int MMAL_PARAM_EXPOSUREMODE_AUTO ; 
 int MMAL_PARAM_EXPOSUREMODE_OFF ; 
 scalar_t__ V4L2_CID_EXPOSURE_AUTO_PRIORITY ; 
#define  V4L2_EXPOSURE_AUTO 129 
#define  V4L2_EXPOSURE_MANUAL 128 
 scalar_t__ V4L2_SCENE_MODE_NONE ; 
 scalar_t__ set_framerate_params (struct bm2835_mmal_dev*) ; 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,struct vchiq_mmal_port*,scalar_t__,int*,int) ; 

__attribute__((used)) static int ctrl_set_exposure(struct bm2835_mmal_dev *dev,
			     struct v4l2_ctrl *ctrl,
			     const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	enum mmal_parameter_exposuremode exp_mode = dev->exposure_mode_user;
	u32 shutter_speed = 0;
	struct vchiq_mmal_port *control;
	int ret = 0;

	control = &dev->component[COMP_CAMERA]->control;

	if (mmal_ctrl->mmal_id == MMAL_PARAMETER_SHUTTER_SPEED)	{
		/* V4L2 is in 100usec increments.
		 * MMAL is 1usec.
		 */
		dev->manual_shutter_speed = ctrl->val * 100;
	} else if (mmal_ctrl->mmal_id == MMAL_PARAMETER_EXPOSURE_MODE) {
		switch (ctrl->val) {
		case V4L2_EXPOSURE_AUTO:
			exp_mode = MMAL_PARAM_EXPOSUREMODE_AUTO;
			break;

		case V4L2_EXPOSURE_MANUAL:
			exp_mode = MMAL_PARAM_EXPOSUREMODE_OFF;
			break;
		}
		dev->exposure_mode_user = exp_mode;
		dev->exposure_mode_v4l2_user = ctrl->val;
	} else if (mmal_ctrl->id == V4L2_CID_EXPOSURE_AUTO_PRIORITY) {
		dev->exp_auto_priority = ctrl->val;
	}

	if (dev->scene_mode == V4L2_SCENE_MODE_NONE) {
		if (exp_mode == MMAL_PARAM_EXPOSUREMODE_OFF)
			shutter_speed = dev->manual_shutter_speed;

		ret = vchiq_mmal_port_parameter_set(dev->instance,
						    control,
						    MMAL_PARAMETER_SHUTTER_SPEED,
						    &shutter_speed,
						    sizeof(shutter_speed));
		ret += vchiq_mmal_port_parameter_set(dev->instance,
						     control,
						     MMAL_PARAMETER_EXPOSURE_MODE,
						     &exp_mode,
						     sizeof(u32));
		dev->exposure_mode_active = exp_mode;
	}
	/* exposure_dynamic_framerate (V4L2_CID_EXPOSURE_AUTO_PRIORITY) should
	 * always apply irrespective of scene mode.
	 */
	ret += set_framerate_params(dev);

	return ret;
}