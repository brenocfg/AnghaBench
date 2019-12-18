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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_enable_dc9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hsw_enable_pc8 (struct drm_i915_private*) ; 

void intel_display_power_suspend_late(struct drm_i915_private *i915)
{
	if (INTEL_GEN(i915) >= 11 || IS_GEN9_LP(i915))
		bxt_enable_dc9(i915);
	else if (IS_HASWELL(i915) || IS_BROADWELL(i915))
		hsw_enable_pc8(i915);
}