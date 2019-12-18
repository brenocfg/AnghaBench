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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ rps; } ;
struct drm_i915_private {TYPE_2__ gt_pm; } ;

/* Variables and functions */
 scalar_t__ HAS_LLC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  __intel_disable_rc6 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_disable_llc_pstate (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_disable_rps (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_disable_gt_powersave(struct drm_i915_private *dev_priv)
{
	mutex_lock(&dev_priv->gt_pm.rps.lock);

	__intel_disable_rc6(dev_priv);
	intel_disable_rps(dev_priv);
	if (HAS_LLC(dev_priv))
		intel_disable_llc_pstate(dev_priv);

	mutex_unlock(&dev_priv->gt_pm.rps.lock);
}