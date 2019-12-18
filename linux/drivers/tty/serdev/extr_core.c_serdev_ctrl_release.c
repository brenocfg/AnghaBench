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
struct serdev_controller {int /*<<< orphan*/  nr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct serdev_controller*) ; 
 struct serdev_controller* to_serdev_controller (struct device*) ; 

__attribute__((used)) static void serdev_ctrl_release(struct device *dev)
{
	struct serdev_controller *ctrl = to_serdev_controller(dev);
	ida_simple_remove(&ctrl_ida, ctrl->nr);
	kfree(ctrl);
}