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
struct drm_i915_private {int /*<<< orphan*/  irq_lock; scalar_t__ display_irqs_enabled; int /*<<< orphan*/  gt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_MASTER_IRQ ; 
 int /*<<< orphan*/  GEN8_MASTER_IRQ_CONTROL ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen8_gt_irq_postinstall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlv_display_irq_postinstall (struct drm_i915_private*) ; 

__attribute__((used)) static void cherryview_irq_postinstall(struct drm_i915_private *dev_priv)
{
	gen8_gt_irq_postinstall(&dev_priv->gt);

	spin_lock_irq(&dev_priv->irq_lock);
	if (dev_priv->display_irqs_enabled)
		vlv_display_irq_postinstall(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);

	I915_WRITE(GEN8_MASTER_IRQ, GEN8_MASTER_IRQ_CONTROL);
	POSTING_READ(GEN8_MASTER_IRQ);
}