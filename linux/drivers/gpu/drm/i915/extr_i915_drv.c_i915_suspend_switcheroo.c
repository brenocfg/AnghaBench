#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ switch_power_state; } ;
struct drm_i915_private {TYPE_3__ drm; } ;
struct TYPE_5__ {scalar_t__ event; } ;
typedef  TYPE_1__ pm_message_t ;

/* Variables and functions */
 scalar_t__ DRM_SWITCH_POWER_OFF ; 
 int EINVAL ; 
 scalar_t__ PM_EVENT_FREEZE ; 
 scalar_t__ PM_EVENT_SUSPEND ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int i915_drm_suspend (TYPE_3__*) ; 
 int i915_drm_suspend_late (TYPE_3__*,int) ; 

__attribute__((used)) static int
i915_suspend_switcheroo(struct drm_i915_private *i915, pm_message_t state)
{
	int error;

	if (WARN_ON_ONCE(state.event != PM_EVENT_SUSPEND &&
			 state.event != PM_EVENT_FREEZE))
		return -EINVAL;

	if (i915->drm.switch_power_state == DRM_SWITCH_POWER_OFF)
		return 0;

	error = i915_drm_suspend(&i915->drm);
	if (error)
		return error;

	return i915_drm_suspend_late(&i915->drm, false);
}