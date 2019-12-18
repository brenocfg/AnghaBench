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
typedef  int /*<<< orphan*/  u32_value ;
typedef  int /*<<< orphan*/  u32 ;
struct vchiq_mmal_port {int dummy; } ;
struct v4l2_ctrl {int val; } ;
struct bm2835_mmal_v4l2_ctrl {int /*<<< orphan*/  mmal_id; } ;
struct bm2835_mmal_dev {int /*<<< orphan*/  instance; TYPE_1__** component; } ;
struct TYPE_2__ {struct vchiq_mmal_port control; } ;

/* Variables and functions */
 size_t COMP_CAMERA ; 
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_AUTO ; 
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_CLOUDY ; 
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_FLASH ; 
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_FLUORESCENT ; 
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_HORIZON ; 
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_INCANDESCENT ; 
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_OFF ; 
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_SHADE ; 
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_SUNLIGHT ; 
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_TUNGSTEN ; 
#define  V4L2_WHITE_BALANCE_AUTO 137 
#define  V4L2_WHITE_BALANCE_CLOUDY 136 
#define  V4L2_WHITE_BALANCE_DAYLIGHT 135 
#define  V4L2_WHITE_BALANCE_FLASH 134 
#define  V4L2_WHITE_BALANCE_FLUORESCENT 133 
#define  V4L2_WHITE_BALANCE_FLUORESCENT_H 132 
#define  V4L2_WHITE_BALANCE_HORIZON 131 
#define  V4L2_WHITE_BALANCE_INCANDESCENT 130 
#define  V4L2_WHITE_BALANCE_MANUAL 129 
#define  V4L2_WHITE_BALANCE_SHADE 128 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,struct vchiq_mmal_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ctrl_set_awb_mode(struct bm2835_mmal_dev *dev,
			     struct v4l2_ctrl *ctrl,
			     const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	u32 u32_value;
	struct vchiq_mmal_port *control;

	control = &dev->component[COMP_CAMERA]->control;

	switch (ctrl->val) {
	case V4L2_WHITE_BALANCE_MANUAL:
		u32_value = MMAL_PARAM_AWBMODE_OFF;
		break;

	case V4L2_WHITE_BALANCE_AUTO:
		u32_value = MMAL_PARAM_AWBMODE_AUTO;
		break;

	case V4L2_WHITE_BALANCE_INCANDESCENT:
		u32_value = MMAL_PARAM_AWBMODE_INCANDESCENT;
		break;

	case V4L2_WHITE_BALANCE_FLUORESCENT:
		u32_value = MMAL_PARAM_AWBMODE_FLUORESCENT;
		break;

	case V4L2_WHITE_BALANCE_FLUORESCENT_H:
		u32_value = MMAL_PARAM_AWBMODE_TUNGSTEN;
		break;

	case V4L2_WHITE_BALANCE_HORIZON:
		u32_value = MMAL_PARAM_AWBMODE_HORIZON;
		break;

	case V4L2_WHITE_BALANCE_DAYLIGHT:
		u32_value = MMAL_PARAM_AWBMODE_SUNLIGHT;
		break;

	case V4L2_WHITE_BALANCE_FLASH:
		u32_value = MMAL_PARAM_AWBMODE_FLASH;
		break;

	case V4L2_WHITE_BALANCE_CLOUDY:
		u32_value = MMAL_PARAM_AWBMODE_CLOUDY;
		break;

	case V4L2_WHITE_BALANCE_SHADE:
		u32_value = MMAL_PARAM_AWBMODE_SHADE;
		break;
	}

	return vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &u32_value, sizeof(u32_value));
}