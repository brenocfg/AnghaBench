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
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int interrupts_enabled; } ;
struct drm_i915_private {TYPE_2__ drm; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  pm_guc_events; TYPE_1__ guc; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_rpm_wakelock_held (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_disable_pm_irq (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen9_reset_guc_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

void gen9_disable_guc_interrupts(struct drm_i915_private *dev_priv)
{
	assert_rpm_wakelock_held(dev_priv);

	spin_lock_irq(&dev_priv->irq_lock);
	dev_priv->guc.interrupts_enabled = false;

	gen6_disable_pm_irq(dev_priv, dev_priv->pm_guc_events);

	spin_unlock_irq(&dev_priv->irq_lock);
	synchronize_irq(dev_priv->drm.irq);

	gen9_reset_guc_interrupts(dev_priv);
}