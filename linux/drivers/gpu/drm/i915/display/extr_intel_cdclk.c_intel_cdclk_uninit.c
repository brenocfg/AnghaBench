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
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_uninit_cdclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cnl_uninit_cdclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  icl_uninit_cdclk (struct drm_i915_private*) ; 
 int /*<<< orphan*/  skl_uninit_cdclk (struct drm_i915_private*) ; 

void intel_cdclk_uninit(struct drm_i915_private *i915)
{
	if (INTEL_GEN(i915) >= 11)
		icl_uninit_cdclk(i915);
	else if (IS_CANNONLAKE(i915))
		cnl_uninit_cdclk(i915);
	else if (IS_GEN9_BC(i915))
		skl_uninit_cdclk(i915);
	else if (IS_GEN9_LP(i915))
		bxt_uninit_cdclk(i915);
}