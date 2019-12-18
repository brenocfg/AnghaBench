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
 int /*<<< orphan*/  MMAL_PARAM_FLICKERAVOID_50HZ ; 
 int /*<<< orphan*/  MMAL_PARAM_FLICKERAVOID_60HZ ; 
 int /*<<< orphan*/  MMAL_PARAM_FLICKERAVOID_AUTO ; 
 int /*<<< orphan*/  MMAL_PARAM_FLICKERAVOID_OFF ; 
#define  V4L2_CID_POWER_LINE_FREQUENCY_50HZ 131 
#define  V4L2_CID_POWER_LINE_FREQUENCY_60HZ 130 
#define  V4L2_CID_POWER_LINE_FREQUENCY_AUTO 129 
#define  V4L2_CID_POWER_LINE_FREQUENCY_DISABLED 128 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,struct vchiq_mmal_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ctrl_set_flicker_avoidance(struct bm2835_mmal_dev *dev,
				      struct v4l2_ctrl *ctrl,
				      const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	u32 u32_value;
	struct vchiq_mmal_port *control;

	control = &dev->component[COMP_CAMERA]->control;

	switch (ctrl->val) {
	case V4L2_CID_POWER_LINE_FREQUENCY_DISABLED:
		u32_value = MMAL_PARAM_FLICKERAVOID_OFF;
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY_50HZ:
		u32_value = MMAL_PARAM_FLICKERAVOID_50HZ;
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY_60HZ:
		u32_value = MMAL_PARAM_FLICKERAVOID_60HZ;
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY_AUTO:
		u32_value = MMAL_PARAM_FLICKERAVOID_AUTO;
		break;
	}

	return vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &u32_value, sizeof(u32_value));
}