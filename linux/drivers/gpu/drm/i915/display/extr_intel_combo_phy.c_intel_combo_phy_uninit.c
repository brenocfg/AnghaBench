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
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cnl_combo_phys_uninit (struct drm_i915_private*) ; 
 int /*<<< orphan*/  icl_combo_phys_uninit (struct drm_i915_private*) ; 

void intel_combo_phy_uninit(struct drm_i915_private *i915)
{
	if (INTEL_GEN(i915) >= 11)
		icl_combo_phys_uninit(i915);
	else if (IS_CANNONLAKE(i915))
		cnl_combo_phys_uninit(i915);
}