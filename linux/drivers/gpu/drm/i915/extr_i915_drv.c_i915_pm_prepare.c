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
struct TYPE_2__ {scalar_t__ switch_power_state; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_SWITCH_POWER_OFF ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int i915_drm_prepare (TYPE_1__*) ; 
 struct drm_i915_private* kdev_to_i915 (struct device*) ; 

__attribute__((used)) static int i915_pm_prepare(struct device *kdev)
{
	struct drm_i915_private *i915 = kdev_to_i915(kdev);

	if (!i915) {
		dev_err(kdev, "DRM not initialized, aborting suspend.\n");
		return -ENODEV;
	}

	if (i915->drm.switch_power_state == DRM_SWITCH_POWER_OFF)
		return 0;

	return i915_drm_prepare(&i915->drm);
}