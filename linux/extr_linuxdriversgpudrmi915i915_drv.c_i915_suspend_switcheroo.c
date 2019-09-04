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
struct TYPE_3__ {scalar_t__ event; } ;
typedef  TYPE_1__ pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 scalar_t__ DRM_SWITCH_POWER_OFF ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ PM_EVENT_FREEZE ; 
 scalar_t__ PM_EVENT_SUSPEND ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int i915_drm_suspend (struct drm_device*) ; 
 int i915_drm_suspend_late (struct drm_device*,int) ; 

__attribute__((used)) static int i915_suspend_switcheroo(struct drm_device *dev, pm_message_t state)
{
	int error;

	if (!dev) {
		DRM_ERROR("dev: %p\n", dev);
		DRM_ERROR("DRM not initialized, aborting suspend.\n");
		return -ENODEV;
	}

	if (WARN_ON_ONCE(state.event != PM_EVENT_SUSPEND &&
			 state.event != PM_EVENT_FREEZE))
		return -EINVAL;

	if (dev->switch_power_state == DRM_SWITCH_POWER_OFF)
		return 0;

	error = i915_drm_suspend(dev);
	if (error)
		return error;

	return i915_drm_suspend_late(dev, false);
}