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
typedef  int /*<<< orphan*/  u32_value ;
typedef  int u32 ;
struct vchiq_mmal_component {int /*<<< orphan*/ * output; } ;
struct v4l2_ctrl {int val; } ;
struct bm2835_mmal_v4l2_ctrl {int /*<<< orphan*/  mmal_id; } ;
struct bm2835_mmal_dev {int /*<<< orphan*/  instance; struct vchiq_mmal_component** component; } ;

/* Variables and functions */
 size_t COMP_CAMERA ; 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ctrl_set_rotate(struct bm2835_mmal_dev *dev,
			   struct v4l2_ctrl *ctrl,
			   const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	int ret;
	u32 u32_value;
	struct vchiq_mmal_component *camera;

	camera = dev->component[COMP_CAMERA];

	u32_value = ((ctrl->val % 360) / 90) * 90;

	ret = vchiq_mmal_port_parameter_set(dev->instance, &camera->output[0],
					    mmal_ctrl->mmal_id,
					    &u32_value, sizeof(u32_value));
	if (ret < 0)
		return ret;

	ret = vchiq_mmal_port_parameter_set(dev->instance, &camera->output[1],
					    mmal_ctrl->mmal_id,
					    &u32_value, sizeof(u32_value));
	if (ret < 0)
		return ret;

	return vchiq_mmal_port_parameter_set(dev->instance, &camera->output[2],
					    mmal_ctrl->mmal_id,
					    &u32_value, sizeof(u32_value));
}