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
struct TYPE_2__ {int interrupts_enabled; } ;
struct drm_i915_private {int pm_guc_events; int /*<<< orphan*/  irq_lock; TYPE_1__ guc; } ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_enable_pm_irq (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen6_pm_iir (struct drm_i915_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen9_enable_guc_interrupts(struct drm_i915_private *dev_priv)
{
	assert_rpm_wakelock_held(dev_priv);

	spin_lock_irq(&dev_priv->irq_lock);
	if (!dev_priv->guc.interrupts_enabled) {
		WARN_ON_ONCE(I915_READ(gen6_pm_iir(dev_priv)) &
				       dev_priv->pm_guc_events);
		dev_priv->guc.interrupts_enabled = true;
		gen6_enable_pm_irq(dev_priv, dev_priv->pm_guc_events);
	}
	spin_unlock_irq(&dev_priv->irq_lock);
}