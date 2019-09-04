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
struct rmi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  rmi_disable_irq (struct rmi_device*,int) ; 
 int rmi_suspend_functions (struct rmi_device*) ; 

int rmi_driver_suspend(struct rmi_device *rmi_dev, bool enable_wake)
{
	int retval;

	retval = rmi_suspend_functions(rmi_dev);
	if (retval)
		dev_warn(&rmi_dev->dev, "Failed to suspend functions: %d\n",
			retval);

	rmi_disable_irq(rmi_dev, enable_wake);
	return retval;
}