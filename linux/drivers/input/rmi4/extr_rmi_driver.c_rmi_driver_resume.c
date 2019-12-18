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
 int /*<<< orphan*/  rmi_enable_irq (struct rmi_device*,int) ; 
 int rmi_resume_functions (struct rmi_device*) ; 

int rmi_driver_resume(struct rmi_device *rmi_dev, bool clear_wake)
{
	int retval;

	rmi_enable_irq(rmi_dev, clear_wake);

	retval = rmi_resume_functions(rmi_dev);
	if (retval)
		dev_warn(&rmi_dev->dev, "Failed to suspend functions: %d\n",
			retval);

	return retval;
}