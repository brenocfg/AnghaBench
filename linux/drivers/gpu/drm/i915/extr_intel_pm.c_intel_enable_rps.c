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
struct intel_rps {int enabled; scalar_t__ max_freq; scalar_t__ min_freq; scalar_t__ idle_freq; scalar_t__ efficient_freq; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_IRONLAKE_M (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cherryview_enable_rps (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_enable_rps (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen8_enable_rps (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_enable_rps (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_init_emon (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ironlake_enable_drps (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  valleyview_enable_rps (struct drm_i915_private*) ; 

__attribute__((used)) static void intel_enable_rps(struct drm_i915_private *dev_priv)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;

	lockdep_assert_held(&rps->lock);

	if (rps->enabled)
		return;

	if (IS_CHERRYVIEW(dev_priv)) {
		cherryview_enable_rps(dev_priv);
	} else if (IS_VALLEYVIEW(dev_priv)) {
		valleyview_enable_rps(dev_priv);
	} else if (INTEL_GEN(dev_priv) >= 9) {
		gen9_enable_rps(dev_priv);
	} else if (IS_BROADWELL(dev_priv)) {
		gen8_enable_rps(dev_priv);
	} else if (INTEL_GEN(dev_priv) >= 6) {
		gen6_enable_rps(dev_priv);
	} else if (IS_IRONLAKE_M(dev_priv)) {
		ironlake_enable_drps(dev_priv);
		intel_init_emon(dev_priv);
	}

	WARN_ON(rps->max_freq < rps->min_freq);
	WARN_ON(rps->idle_freq > rps->max_freq);

	WARN_ON(rps->efficient_freq < rps->min_freq);
	WARN_ON(rps->efficient_freq > rps->max_freq);

	rps->enabled = true;
}