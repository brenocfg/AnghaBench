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
struct TYPE_2__ {int num_power_states; scalar_t__ pm_method; int /*<<< orphan*/  power_state; int /*<<< orphan*/  dynpm_idle_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dynpm_planned_action; int /*<<< orphan*/  dynpm_state; int /*<<< orphan*/  profile; } ;
struct radeon_device {TYPE_1__ pm; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DYNPM_ACTION_DEFAULT ; 
 int /*<<< orphan*/  DYNPM_STATE_DISABLED ; 
 scalar_t__ PM_METHOD_DYNPM ; 
 scalar_t__ PM_METHOD_PROFILE ; 
 int /*<<< orphan*/  PM_PROFILE_DEFAULT ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_power_method ; 
 int /*<<< orphan*/  dev_attr_power_profile ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_hwmon_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_set_clocks (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_update_profile (struct radeon_device*) ; 

__attribute__((used)) static void radeon_pm_fini_old(struct radeon_device *rdev)
{
	if (rdev->pm.num_power_states > 1) {
		mutex_lock(&rdev->pm.mutex);
		if (rdev->pm.pm_method == PM_METHOD_PROFILE) {
			rdev->pm.profile = PM_PROFILE_DEFAULT;
			radeon_pm_update_profile(rdev);
			radeon_pm_set_clocks(rdev);
		} else if (rdev->pm.pm_method == PM_METHOD_DYNPM) {
			/* reset default clocks */
			rdev->pm.dynpm_state = DYNPM_STATE_DISABLED;
			rdev->pm.dynpm_planned_action = DYNPM_ACTION_DEFAULT;
			radeon_pm_set_clocks(rdev);
		}
		mutex_unlock(&rdev->pm.mutex);

		cancel_delayed_work_sync(&rdev->pm.dynpm_idle_work);

		device_remove_file(rdev->dev, &dev_attr_power_profile);
		device_remove_file(rdev->dev, &dev_attr_power_method);
	}

	radeon_hwmon_fini(rdev);
	kfree(rdev->pm.power_state);
}