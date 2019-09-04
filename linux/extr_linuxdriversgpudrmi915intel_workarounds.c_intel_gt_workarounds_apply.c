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
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  bdw_gt_workarounds_apply (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_gt_workarounds_apply (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cfl_gt_workarounds_apply (struct drm_i915_private*) ; 
 int /*<<< orphan*/  chv_gt_workarounds_apply (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cnl_gt_workarounds_apply (struct drm_i915_private*) ; 
 int /*<<< orphan*/  glk_gt_workarounds_apply (struct drm_i915_private*) ; 
 int /*<<< orphan*/  icl_gt_workarounds_apply (struct drm_i915_private*) ; 
 int /*<<< orphan*/  kbl_gt_workarounds_apply (struct drm_i915_private*) ; 
 int /*<<< orphan*/  skl_gt_workarounds_apply (struct drm_i915_private*) ; 

void intel_gt_workarounds_apply(struct drm_i915_private *dev_priv)
{
	if (INTEL_GEN(dev_priv) < 8)
		return;
	else if (IS_BROADWELL(dev_priv))
		bdw_gt_workarounds_apply(dev_priv);
	else if (IS_CHERRYVIEW(dev_priv))
		chv_gt_workarounds_apply(dev_priv);
	else if (IS_SKYLAKE(dev_priv))
		skl_gt_workarounds_apply(dev_priv);
	else if (IS_BROXTON(dev_priv))
		bxt_gt_workarounds_apply(dev_priv);
	else if (IS_KABYLAKE(dev_priv))
		kbl_gt_workarounds_apply(dev_priv);
	else if (IS_GEMINILAKE(dev_priv))
		glk_gt_workarounds_apply(dev_priv);
	else if (IS_COFFEELAKE(dev_priv))
		cfl_gt_workarounds_apply(dev_priv);
	else if (IS_CANNONLAKE(dev_priv))
		cnl_gt_workarounds_apply(dev_priv);
	else if (IS_ICELAKE(dev_priv))
		icl_gt_workarounds_apply(dev_priv);
	else
		MISSING_CASE(INTEL_GEN(dev_priv));
}