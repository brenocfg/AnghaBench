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
struct TYPE_2__ {int allowed_dc_mask; scalar_t__ dmc_payload; } ;
struct drm_i915_private {TYPE_1__ csr; } ;

/* Variables and functions */
 int DC_STATE_EN_UPTO_DC5 ; 
 int DC_STATE_EN_UPTO_DC6 ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_disable_dc9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_display_core_init (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen9_enable_dc5 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  hsw_disable_pc8 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  icl_display_core_init (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  skl_enable_dc6 (struct drm_i915_private*) ; 

void intel_display_power_resume(struct drm_i915_private *i915)
{
	if (INTEL_GEN(i915) >= 11) {
		bxt_disable_dc9(i915);
		icl_display_core_init(i915, true);
		if (i915->csr.dmc_payload) {
			if (i915->csr.allowed_dc_mask &
			    DC_STATE_EN_UPTO_DC6)
				skl_enable_dc6(i915);
			else if (i915->csr.allowed_dc_mask &
				 DC_STATE_EN_UPTO_DC5)
				gen9_enable_dc5(i915);
		}
	} else if (IS_GEN9_LP(i915)) {
		bxt_disable_dc9(i915);
		bxt_display_core_init(i915, true);
		if (i915->csr.dmc_payload &&
		    (i915->csr.allowed_dc_mask & DC_STATE_EN_UPTO_DC5))
			gen9_enable_dc5(i915);
	} else if (IS_HASWELL(i915) || IS_BROADWELL(i915)) {
		hsw_disable_pc8(i915);
	}
}