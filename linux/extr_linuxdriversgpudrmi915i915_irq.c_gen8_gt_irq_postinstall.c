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
typedef  int uint32_t ;
struct drm_i915_private {int pm_ier; int pm_imr; } ;

/* Variables and functions */
 int GEN8_BCS_IRQ_SHIFT ; 
 int /*<<< orphan*/  GEN8_IRQ_INIT_NDX (int /*<<< orphan*/ ,int,int,int) ; 
 int GEN8_RCS_IRQ_SHIFT ; 
 int GEN8_VCS1_IRQ_SHIFT ; 
 int GEN8_VCS2_IRQ_SHIFT ; 
 int GEN8_VECS_IRQ_SHIFT ; 
 int /*<<< orphan*/  GT ; 
 int GT_CONTEXT_SWITCH_INTERRUPT ; 
 int GT_RENDER_L3_PARITY_ERROR_INTERRUPT ; 
 int GT_RENDER_USER_INTERRUPT ; 
 scalar_t__ HAS_L3_DPF (struct drm_i915_private*) ; 

__attribute__((used)) static void gen8_gt_irq_postinstall(struct drm_i915_private *dev_priv)
{
	/* These are interrupts we'll toggle with the ring mask register */
	uint32_t gt_interrupts[] = {
		GT_RENDER_USER_INTERRUPT << GEN8_RCS_IRQ_SHIFT |
			GT_CONTEXT_SWITCH_INTERRUPT << GEN8_RCS_IRQ_SHIFT |
			GT_RENDER_USER_INTERRUPT << GEN8_BCS_IRQ_SHIFT |
			GT_CONTEXT_SWITCH_INTERRUPT << GEN8_BCS_IRQ_SHIFT,
		GT_RENDER_USER_INTERRUPT << GEN8_VCS1_IRQ_SHIFT |
			GT_CONTEXT_SWITCH_INTERRUPT << GEN8_VCS1_IRQ_SHIFT |
			GT_RENDER_USER_INTERRUPT << GEN8_VCS2_IRQ_SHIFT |
			GT_CONTEXT_SWITCH_INTERRUPT << GEN8_VCS2_IRQ_SHIFT,
		0,
		GT_RENDER_USER_INTERRUPT << GEN8_VECS_IRQ_SHIFT |
			GT_CONTEXT_SWITCH_INTERRUPT << GEN8_VECS_IRQ_SHIFT
		};

	if (HAS_L3_DPF(dev_priv))
		gt_interrupts[0] |= GT_RENDER_L3_PARITY_ERROR_INTERRUPT;

	dev_priv->pm_ier = 0x0;
	dev_priv->pm_imr = ~dev_priv->pm_ier;
	GEN8_IRQ_INIT_NDX(GT, 0, ~gt_interrupts[0], gt_interrupts[0]);
	GEN8_IRQ_INIT_NDX(GT, 1, ~gt_interrupts[1], gt_interrupts[1]);
	/*
	 * RPS interrupts will get enabled/disabled on demand when RPS itself
	 * is enabled/disabled. Same wil be the case for GuC interrupts.
	 */
	GEN8_IRQ_INIT_NDX(GT, 2, dev_priv->pm_imr, dev_priv->pm_ier);
	GEN8_IRQ_INIT_NDX(GT, 3, ~gt_interrupts[3], gt_interrupts[3]);
}