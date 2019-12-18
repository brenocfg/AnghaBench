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
struct spmi_controller {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spmi_ctrl_remove_device ; 

void spmi_controller_remove(struct spmi_controller *ctrl)
{
	int dummy;

	if (!ctrl)
		return;

	dummy = device_for_each_child(&ctrl->dev, NULL,
				      spmi_ctrl_remove_device);
	device_del(&ctrl->dev);
}