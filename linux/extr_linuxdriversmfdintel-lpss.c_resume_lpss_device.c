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
 int /*<<< orphan*/  dev_pm_test_driver_flags (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_resume (struct device*) ; 

__attribute__((used)) static int resume_lpss_device(struct device *dev, void *data)
{
	if (!dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_SUSPEND))
		pm_runtime_resume(dev);

	return 0;
}