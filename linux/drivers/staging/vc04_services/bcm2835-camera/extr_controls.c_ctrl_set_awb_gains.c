#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vchiq_mmal_port {int dummy; } ;
struct v4l2_ctrl {scalar_t__ id; int /*<<< orphan*/  val; } ;
struct TYPE_6__ {int den; int /*<<< orphan*/  num; } ;
struct TYPE_5__ {int den; int /*<<< orphan*/  num; } ;
struct mmal_parameter_awbgains {TYPE_3__ b_gain; TYPE_2__ r_gain; } ;
struct bm2835_mmal_v4l2_ctrl {int /*<<< orphan*/  mmal_id; } ;
struct bm2835_mmal_dev {int /*<<< orphan*/  instance; int /*<<< orphan*/  blue_gain; int /*<<< orphan*/  red_gain; TYPE_1__** component; } ;
typedef  int /*<<< orphan*/  gains ;
struct TYPE_4__ {struct vchiq_mmal_port control; } ;

/* Variables and functions */
 size_t COMP_CAMERA ; 
 scalar_t__ V4L2_CID_BLUE_BALANCE ; 
 scalar_t__ V4L2_CID_RED_BALANCE ; 
 int vchiq_mmal_port_parameter_set (int /*<<< orphan*/ ,struct vchiq_mmal_port*,int /*<<< orphan*/ ,struct mmal_parameter_awbgains*,int) ; 

__attribute__((used)) static int ctrl_set_awb_gains(struct bm2835_mmal_dev *dev,
			      struct v4l2_ctrl *ctrl,
			      const struct bm2835_mmal_v4l2_ctrl *mmal_ctrl)
{
	struct vchiq_mmal_port *control;
	struct mmal_parameter_awbgains gains;

	control = &dev->component[COMP_CAMERA]->control;

	if (ctrl->id == V4L2_CID_RED_BALANCE)
		dev->red_gain = ctrl->val;
	else if (ctrl->id == V4L2_CID_BLUE_BALANCE)
		dev->blue_gain = ctrl->val;

	gains.r_gain.num = dev->red_gain;
	gains.b_gain.num = dev->blue_gain;
	gains.r_gain.den = gains.b_gain.den = 1000;

	return vchiq_mmal_port_parameter_set(dev->instance, control,
					     mmal_ctrl->mmal_id,
					     &gains, sizeof(gains));
}