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
struct TYPE_2__ {scalar_t__ pm_method; int /*<<< orphan*/  dynpm_idle_work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dynpm_planned_action; int /*<<< orphan*/  dynpm_state; } ;
struct radeon_device {int flags; TYPE_1__ pm; } ;
struct drm_device {scalar_t__ switch_power_state; struct radeon_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ DRM_SWITCH_POWER_ON ; 
 int /*<<< orphan*/  DYNPM_ACTION_DEFAULT ; 
 int /*<<< orphan*/  DYNPM_ACTION_NONE ; 
 int /*<<< orphan*/  DYNPM_STATE_DISABLED ; 
 int /*<<< orphan*/  DYNPM_STATE_PAUSED ; 
 size_t EINVAL ; 
 scalar_t__ PM_METHOD_DPM ; 
 scalar_t__ PM_METHOD_DYNPM ; 
 scalar_t__ PM_METHOD_PROFILE ; 
 int RADEON_IS_PX ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_pm_compute_clocks (struct radeon_device*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t radeon_set_pm_method(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf,
				    size_t count)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct radeon_device *rdev = ddev->dev_private;

	/* Can't set method when the card is off */
	if  ((rdev->flags & RADEON_IS_PX) &&
	     (ddev->switch_power_state != DRM_SWITCH_POWER_ON)) {
		count = -EINVAL;
		goto fail;
	}

	/* we don't support the legacy modes with dpm */
	if (rdev->pm.pm_method == PM_METHOD_DPM) {
		count = -EINVAL;
		goto fail;
	}

	if (strncmp("dynpm", buf, strlen("dynpm")) == 0) {
		mutex_lock(&rdev->pm.mutex);
		rdev->pm.pm_method = PM_METHOD_DYNPM;
		rdev->pm.dynpm_state = DYNPM_STATE_PAUSED;
		rdev->pm.dynpm_planned_action = DYNPM_ACTION_DEFAULT;
		mutex_unlock(&rdev->pm.mutex);
	} else if (strncmp("profile", buf, strlen("profile")) == 0) {
		mutex_lock(&rdev->pm.mutex);
		/* disable dynpm */
		rdev->pm.dynpm_state = DYNPM_STATE_DISABLED;
		rdev->pm.dynpm_planned_action = DYNPM_ACTION_NONE;
		rdev->pm.pm_method = PM_METHOD_PROFILE;
		mutex_unlock(&rdev->pm.mutex);
		cancel_delayed_work_sync(&rdev->pm.dynpm_idle_work);
	} else {
		count = -EINVAL;
		goto fail;
	}
	radeon_pm_compute_clocks(rdev);
fail:
	return count;
}