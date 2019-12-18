#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_RC6 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_rc6_ctx_wa_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  valleyview_cleanup_gt_powersave (struct drm_i915_private*) ; 

void intel_cleanup_gt_powersave(struct drm_i915_private *dev_priv)
{
	if (IS_VALLEYVIEW(dev_priv))
		valleyview_cleanup_gt_powersave(dev_priv);

	i915_rc6_ctx_wa_cleanup(dev_priv);

	if (!HAS_RC6(dev_priv))
		pm_runtime_put(&dev_priv->drm.pdev->dev);
}