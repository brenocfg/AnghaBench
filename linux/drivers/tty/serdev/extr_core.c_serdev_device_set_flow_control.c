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
struct serdev_device {struct serdev_controller* ctrl; } ;
struct serdev_controller {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_flow_control ) (struct serdev_controller*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct serdev_controller*,int) ; 

void serdev_device_set_flow_control(struct serdev_device *serdev, bool enable)
{
	struct serdev_controller *ctrl = serdev->ctrl;

	if (!ctrl || !ctrl->ops->set_flow_control)
		return;

	ctrl->ops->set_flow_control(ctrl, enable);
}