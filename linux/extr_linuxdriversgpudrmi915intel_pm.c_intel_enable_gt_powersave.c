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
struct drm_i915_private {int /*<<< orphan*/  pcu_lock; } ;

/* Variables and functions */
 scalar_t__ HAS_LLC (struct drm_i915_private*) ; 
 scalar_t__ HAS_RC6 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_enable_llc_pstate (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_enable_rc6 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_enable_rps (struct drm_i915_private*) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_enable_gt_powersave(struct drm_i915_private *dev_priv)
{
	/* Powersaving is controlled by the host when inside a VM */
	if (intel_vgpu_active(dev_priv))
		return;

	mutex_lock(&dev_priv->pcu_lock);

	if (HAS_RC6(dev_priv))
		intel_enable_rc6(dev_priv);
	intel_enable_rps(dev_priv);
	if (HAS_LLC(dev_priv))
		intel_enable_llc_pstate(dev_priv);

	mutex_unlock(&dev_priv->pcu_lock);
}