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
typedef  int u32 ;
struct TYPE_2__ {int which_slice; int /*<<< orphan*/  error_work; } ;
struct drm_i915_private {TYPE_1__ l3_parity; int /*<<< orphan*/  wq; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int GT_PARITY_ERROR (struct drm_i915_private*) ; 
 int GT_RENDER_L3_PARITY_ERROR_INTERRUPT ; 
 int GT_RENDER_L3_PARITY_ERROR_INTERRUPT_S1 ; 
 int /*<<< orphan*/  HAS_L3_DPF (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen5_disable_gt_irq (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ivybridge_parity_error_irq_handler(struct drm_i915_private *dev_priv,
					       u32 iir)
{
	if (!HAS_L3_DPF(dev_priv))
		return;

	spin_lock(&dev_priv->irq_lock);
	gen5_disable_gt_irq(dev_priv, GT_PARITY_ERROR(dev_priv));
	spin_unlock(&dev_priv->irq_lock);

	iir &= GT_PARITY_ERROR(dev_priv);
	if (iir & GT_RENDER_L3_PARITY_ERROR_INTERRUPT_S1)
		dev_priv->l3_parity.which_slice |= 1 << 1;

	if (iir & GT_RENDER_L3_PARITY_ERROR_INTERRUPT)
		dev_priv->l3_parity.which_slice |= 1 << 0;

	queue_work(dev_priv->wq, &dev_priv->l3_parity.error_work);
}