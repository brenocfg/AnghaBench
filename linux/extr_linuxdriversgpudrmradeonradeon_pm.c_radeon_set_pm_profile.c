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
struct TYPE_2__ {scalar_t__ pm_method; int /*<<< orphan*/  mutex; int /*<<< orphan*/  profile; } ;
struct radeon_device {int flags; TYPE_1__ pm; } ;
struct drm_device {scalar_t__ switch_power_state; struct radeon_device* dev_private; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ DRM_SWITCH_POWER_ON ; 
 size_t EINVAL ; 
 scalar_t__ PM_METHOD_PROFILE ; 
 int /*<<< orphan*/  PM_PROFILE_AUTO ; 
 int /*<<< orphan*/  PM_PROFILE_DEFAULT ; 
 int /*<<< orphan*/  PM_PROFILE_HIGH ; 
 int /*<<< orphan*/  PM_PROFILE_LOW ; 
 int /*<<< orphan*/  PM_PROFILE_MID ; 
 int RADEON_IS_PX ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_pm_set_clocks (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_update_profile (struct radeon_device*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t radeon_set_pm_profile(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf,
				     size_t count)
{
	struct drm_device *ddev = dev_get_drvdata(dev);
	struct radeon_device *rdev = ddev->dev_private;

	/* Can't set profile when the card is off */
	if  ((rdev->flags & RADEON_IS_PX) &&
	     (ddev->switch_power_state != DRM_SWITCH_POWER_ON))
		return -EINVAL;

	mutex_lock(&rdev->pm.mutex);
	if (rdev->pm.pm_method == PM_METHOD_PROFILE) {
		if (strncmp("default", buf, strlen("default")) == 0)
			rdev->pm.profile = PM_PROFILE_DEFAULT;
		else if (strncmp("auto", buf, strlen("auto")) == 0)
			rdev->pm.profile = PM_PROFILE_AUTO;
		else if (strncmp("low", buf, strlen("low")) == 0)
			rdev->pm.profile = PM_PROFILE_LOW;
		else if (strncmp("mid", buf, strlen("mid")) == 0)
			rdev->pm.profile = PM_PROFILE_MID;
		else if (strncmp("high", buf, strlen("high")) == 0)
			rdev->pm.profile = PM_PROFILE_HIGH;
		else {
			count = -EINVAL;
			goto fail;
		}
		radeon_pm_update_profile(rdev);
		radeon_pm_set_clocks(rdev);
	} else
		count = -EINVAL;

fail:
	mutex_unlock(&rdev->pm.mutex);

	return count;
}