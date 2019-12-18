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
struct TYPE_2__ {scalar_t__ pm_method; int dpm_enabled; int sysfs_initialized; int num_power_states; int /*<<< orphan*/  mutex; } ;
struct radeon_device {TYPE_1__ pm; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ PM_METHOD_DPM ; 
 int /*<<< orphan*/  dev_attr_power_dpm_force_performance_level ; 
 int /*<<< orphan*/  dev_attr_power_dpm_state ; 
 int /*<<< orphan*/  dev_attr_power_method ; 
 int /*<<< orphan*/  dev_attr_power_profile ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int radeon_dpm_late_enable (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_compute_clocks (struct radeon_device*) ; 

int radeon_pm_late_init(struct radeon_device *rdev)
{
	int ret = 0;

	if (rdev->pm.pm_method == PM_METHOD_DPM) {
		if (rdev->pm.dpm_enabled) {
			if (!rdev->pm.sysfs_initialized) {
				ret = device_create_file(rdev->dev, &dev_attr_power_dpm_state);
				if (ret)
					DRM_ERROR("failed to create device file for dpm state\n");
				ret = device_create_file(rdev->dev, &dev_attr_power_dpm_force_performance_level);
				if (ret)
					DRM_ERROR("failed to create device file for dpm state\n");
				/* XXX: these are noops for dpm but are here for backwards compat */
				ret = device_create_file(rdev->dev, &dev_attr_power_profile);
				if (ret)
					DRM_ERROR("failed to create device file for power profile\n");
				ret = device_create_file(rdev->dev, &dev_attr_power_method);
				if (ret)
					DRM_ERROR("failed to create device file for power method\n");
				rdev->pm.sysfs_initialized = true;
			}

			mutex_lock(&rdev->pm.mutex);
			ret = radeon_dpm_late_enable(rdev);
			mutex_unlock(&rdev->pm.mutex);
			if (ret) {
				rdev->pm.dpm_enabled = false;
				DRM_ERROR("radeon_pm_late_init failed, disabling dpm\n");
			} else {
				/* set the dpm state for PX since there won't be
				 * a modeset to call this.
				 */
				radeon_pm_compute_clocks(rdev);
			}
		}
	} else {
		if ((rdev->pm.num_power_states > 1) &&
		    (!rdev->pm.sysfs_initialized)) {
			/* where's the best place to put these? */
			ret = device_create_file(rdev->dev, &dev_attr_power_profile);
			if (ret)
				DRM_ERROR("failed to create device file for power profile\n");
			ret = device_create_file(rdev->dev, &dev_attr_power_method);
			if (ret)
				DRM_ERROR("failed to create device file for power method\n");
			if (!ret)
				rdev->pm.sysfs_initialized = true;
		}
	}
	return ret;
}