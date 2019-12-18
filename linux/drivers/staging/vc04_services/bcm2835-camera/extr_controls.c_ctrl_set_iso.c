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
typedef  scalar_t__ u32 ;
struct vchiq_mmal_port {int dummy; } ;
struct v4l2_ctrl {size_t val; scalar_t__ id; } ;
struct bm2835_mmal_v4l2_ctrl {size_t max; size_t min; } ;
struct bm2835_mmal_dev {int manual_iso_enabled; int /*<<< orphan*/  instance; scalar_t__ iso; TYPE_1__** component; } ;
struct TYPE_2__ {struct vchiq_mmal_port control; } ;

/* Variables and functions */
 size_t COMP_CAMERA ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ISO ; 
 scalar_t__ V4L2_CID_ISO_SENSITIVITY ; 
 scalar_t__ V4L2_CID_ISO_SENSITIVITY_AUTO ; 
 size_t V4L2_ISO_SENSITIVITY_MANUAL ; 
 scalar_t__* iso_values ; 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,struct vchiq_mmal_port*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int ctrl_set_iso(struct bm2835_mmal_dev *dev,
			struct v4l2_ctrl *ctrl,
			const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	u32 u32_value;
	struct vchiq_mmal_port *control;

	if (ctrl->val > mmal_ctrl->max || ctrl->val < mmal_ctrl->min)
		return 1;

	if (ctrl->id == V4L2_CID_ISO_SENSITIVITY)
		dev->iso = iso_values[ctrl->val];
	else if (ctrl->id == V4L2_CID_ISO_SENSITIVITY_AUTO)
		dev->manual_iso_enabled =
				(ctrl->val == V4L2_ISO_SENSITIVITY_MANUAL);

	control = &dev->component[COMP_CAMERA]->control;

	if (dev->manual_iso_enabled)
		u32_value = dev->iso;
	else
		u32_value = 0;

	return vchiq_mmal_port_parameter_set(dev->instance, control,
					     MMAL_PARAMETER_ISO,
					     &u32_value, sizeof(u32_value));
}