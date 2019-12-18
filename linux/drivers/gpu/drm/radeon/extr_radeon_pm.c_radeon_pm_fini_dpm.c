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
struct TYPE_2__ {int num_power_states; int /*<<< orphan*/  power_state; int /*<<< orphan*/  mutex; } ;
struct radeon_device {TYPE_1__ pm; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_power_dpm_force_performance_level ; 
 int /*<<< orphan*/  dev_attr_power_dpm_state ; 
 int /*<<< orphan*/  dev_attr_power_method ; 
 int /*<<< orphan*/  dev_attr_power_profile ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_dpm_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_dpm_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_hwmon_fini (struct radeon_device*) ; 

__attribute__((used)) static void radeon_pm_fini_dpm(struct radeon_device *rdev)
{
	if (rdev->pm.num_power_states > 1) {
		mutex_lock(&rdev->pm.mutex);
		radeon_dpm_disable(rdev);
		mutex_unlock(&rdev->pm.mutex);

		device_remove_file(rdev->dev, &dev_attr_power_dpm_state);
		device_remove_file(rdev->dev, &dev_attr_power_dpm_force_performance_level);
		/* XXX backwards compat */
		device_remove_file(rdev->dev, &dev_attr_power_profile);
		device_remove_file(rdev->dev, &dev_attr_power_method);
	}
	radeon_dpm_fini(rdev);

	radeon_hwmon_fini(rdev);
	kfree(rdev->pm.power_state);
}