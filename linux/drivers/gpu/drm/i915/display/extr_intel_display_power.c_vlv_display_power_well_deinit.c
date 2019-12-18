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
struct TYPE_6__ {TYPE_2__* dev; } ;
struct drm_i915_private {TYPE_3__ drm; int /*<<< orphan*/  irq_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_suspended; } ;
struct TYPE_5__ {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_hpd_poll_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_power_sequencer_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_synchronize_irq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  valleyview_disable_display_irqs (struct drm_i915_private*) ; 

__attribute__((used)) static void vlv_display_power_well_deinit(struct drm_i915_private *dev_priv)
{
	spin_lock_irq(&dev_priv->irq_lock);
	valleyview_disable_display_irqs(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);

	/* make sure we're done processing display irqs */
	intel_synchronize_irq(dev_priv);

	intel_power_sequencer_reset(dev_priv);

	/* Prevent us from re-enabling polling on accident in late suspend */
	if (!dev_priv->drm.dev->power.is_suspended)
		intel_hpd_poll_init(dev_priv);
}