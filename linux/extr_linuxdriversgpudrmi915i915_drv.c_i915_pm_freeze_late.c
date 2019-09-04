#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device {scalar_t__ switch_power_state; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct drm_device drm; } ;

/* Variables and functions */
 scalar_t__ DRM_SWITCH_POWER_OFF ; 
 int i915_drm_suspend_late (struct drm_device*,int) ; 
 int i915_gem_freeze_late (TYPE_1__*) ; 
 TYPE_1__* kdev_to_i915 (struct device*) ; 

__attribute__((used)) static int i915_pm_freeze_late(struct device *kdev)
{
	struct drm_device *dev = &kdev_to_i915(kdev)->drm;
	int ret;

	if (dev->switch_power_state != DRM_SWITCH_POWER_OFF) {
		ret = i915_drm_suspend_late(dev, true);
		if (ret)
			return ret;
	}

	ret = i915_gem_freeze_late(kdev_to_i915(kdev));
	if (ret)
		return ret;

	return 0;
}