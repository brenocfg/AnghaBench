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
struct drm_i915_private {int /*<<< orphan*/  sb_lock; int /*<<< orphan*/  sb_qos; int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_cleanup_early (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_workqueues_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_driver_late_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_irq_fini (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_domains_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlv_free_s0ix_state (struct drm_i915_private*) ; 

__attribute__((used)) static void i915_driver_late_release(struct drm_i915_private *dev_priv)
{
	intel_irq_fini(dev_priv);
	intel_power_domains_cleanup(dev_priv);
	i915_gem_cleanup_early(dev_priv);
	intel_gt_driver_late_release(&dev_priv->gt);
	vlv_free_s0ix_state(dev_priv);
	i915_workqueues_cleanup(dev_priv);

	pm_qos_remove_request(&dev_priv->sb_qos);
	mutex_destroy(&dev_priv->sb_lock);
}