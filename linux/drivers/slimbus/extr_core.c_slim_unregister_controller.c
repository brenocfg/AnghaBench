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
struct slim_controller {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_ida ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slim_ctrl_clk_pause (struct slim_controller*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slim_ctrl_remove_device ; 

int slim_unregister_controller(struct slim_controller *ctrl)
{
	/* Remove all clients */
	device_for_each_child(ctrl->dev, NULL, slim_ctrl_remove_device);
	/* Enter Clock Pause */
	slim_ctrl_clk_pause(ctrl, false, 0);
	ida_simple_remove(&ctrl_ida, ctrl->id);

	return 0;
}