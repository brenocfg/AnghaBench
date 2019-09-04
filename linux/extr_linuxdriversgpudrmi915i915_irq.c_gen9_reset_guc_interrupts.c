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
struct drm_i915_private {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  pm_guc_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_rpm_wakelock_held (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_reset_pm_iir (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen9_reset_guc_interrupts(struct drm_i915_private *dev_priv)
{
	assert_rpm_wakelock_held(dev_priv);

	spin_lock_irq(&dev_priv->irq_lock);
	gen6_reset_pm_iir(dev_priv, dev_priv->pm_guc_events);
	spin_unlock_irq(&dev_priv->irq_lock);
}