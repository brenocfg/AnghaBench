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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int GEN8_GT_IRQS ; 
 int /*<<< orphan*/  GEN8_MASTER_IRQ ; 
 int GEN8_MASTER_IRQ_CONTROL ; 
 int I915_READ_FW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  disable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  enable_rpm_wakeref_asserts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen8_de_irq_handler (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen8_gt_irq_ack (struct drm_i915_private*,int,int*) ; 
 int /*<<< orphan*/  gen8_gt_irq_handler (struct drm_i915_private*,int,int*) ; 
 int /*<<< orphan*/  intel_irqs_enabled (struct drm_i915_private*) ; 
 struct drm_i915_private* to_i915 (void*) ; 

__attribute__((used)) static irqreturn_t gen8_irq_handler(int irq, void *arg)
{
	struct drm_i915_private *dev_priv = to_i915(arg);
	u32 master_ctl;
	u32 gt_iir[4];

	if (!intel_irqs_enabled(dev_priv))
		return IRQ_NONE;

	master_ctl = I915_READ_FW(GEN8_MASTER_IRQ);
	master_ctl &= ~GEN8_MASTER_IRQ_CONTROL;
	if (!master_ctl)
		return IRQ_NONE;

	I915_WRITE_FW(GEN8_MASTER_IRQ, 0);

	/* Find, clear, then process each source of interrupt */
	gen8_gt_irq_ack(dev_priv, master_ctl, gt_iir);

	/* IRQs are synced during runtime_suspend, we don't require a wakeref */
	if (master_ctl & ~GEN8_GT_IRQS) {
		disable_rpm_wakeref_asserts(dev_priv);
		gen8_de_irq_handler(dev_priv, master_ctl);
		enable_rpm_wakeref_asserts(dev_priv);
	}

	I915_WRITE_FW(GEN8_MASTER_IRQ, GEN8_MASTER_IRQ_CONTROL);

	gen8_gt_irq_handler(dev_priv, master_ctl, gt_iir);

	return IRQ_HANDLED;
}