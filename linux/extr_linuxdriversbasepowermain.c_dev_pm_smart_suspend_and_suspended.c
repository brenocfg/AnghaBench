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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_FLAG_SMART_SUSPEND ; 
 scalar_t__ dev_pm_test_driver_flags (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_runtime_status_suspended (struct device*) ; 

bool dev_pm_smart_suspend_and_suspended(struct device *dev)
{
	return dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_SUSPEND) &&
		pm_runtime_status_suspended(dev);
}