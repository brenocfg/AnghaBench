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
 int /*<<< orphan*/  HAS_RC6 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  valleyview_cleanup_gt_powersave (struct drm_i915_private*) ; 

void intel_cleanup_gt_powersave(struct drm_i915_private *dev_priv)
{
	if (IS_VALLEYVIEW(dev_priv))
		valleyview_cleanup_gt_powersave(dev_priv);

	if (!HAS_RC6(dev_priv))
		intel_runtime_pm_put(dev_priv);
}