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
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASTER_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_MASTER_IER ; 
 int /*<<< orphan*/  gen5_gt_irq_postinstall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlv_display_irq_postinstall (struct drm_i915_private*) ; 

__attribute__((used)) static void valleyview_irq_postinstall(struct drm_i915_private *dev_priv)
{
	gen5_gt_irq_postinstall(&dev_priv->gt);

	spin_lock_irq(&dev_priv->irq_lock);
	if (dev_priv->display_irqs_enabled)
		vlv_display_irq_postinstall(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);

	I915_WRITE(VLV_MASTER_IER, MASTER_INTERRUPT_ENABLE);
	POSTING_READ(VLV_MASTER_IER);
}