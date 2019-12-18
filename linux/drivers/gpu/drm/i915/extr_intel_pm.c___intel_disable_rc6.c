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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {TYPE_2__ rc6; TYPE_1__ rps; } ;
struct drm_i915_private {TYPE_3__ gt_pm; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cherryview_disable_rc6 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_disable_rc6 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_disable_rc6 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  valleyview_disable_rc6 (struct drm_i915_private*) ; 

__attribute__((used)) static void __intel_disable_rc6(struct drm_i915_private *dev_priv)
{
	lockdep_assert_held(&dev_priv->gt_pm.rps.lock);

	if (!dev_priv->gt_pm.rc6.enabled)
		return;

	if (INTEL_GEN(dev_priv) >= 9)
		gen9_disable_rc6(dev_priv);
	else if (IS_CHERRYVIEW(dev_priv))
		cherryview_disable_rc6(dev_priv);
	else if (IS_VALLEYVIEW(dev_priv))
		valleyview_disable_rc6(dev_priv);
	else if (INTEL_GEN(dev_priv) >= 6)
		gen6_disable_rc6(dev_priv);

	dev_priv->gt_pm.rc6.enabled = false;
}