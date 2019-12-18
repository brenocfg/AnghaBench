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
struct intel_uncore {int dummy; } ;
struct intel_gt {int pm_ier; int pm_imr; struct intel_uncore* uncore; } ;

/* Variables and functions */
 int GEN8_BCS_IRQ_SHIFT ; 
 int /*<<< orphan*/  GEN8_IRQ_INIT_NDX (struct intel_uncore*,int /*<<< orphan*/ ,int,int,int) ; 
 int GEN8_RCS_IRQ_SHIFT ; 
 int GEN8_VCS0_IRQ_SHIFT ; 
 int GEN8_VCS1_IRQ_SHIFT ; 
 int GEN8_VECS_IRQ_SHIFT ; 
 int /*<<< orphan*/  GT ; 
 int GT_CONTEXT_SWITCH_INTERRUPT ; 
 int GT_RENDER_USER_INTERRUPT ; 

void gen8_gt_irq_postinstall(struct intel_gt *gt)
{
	struct intel_uncore *uncore = gt->uncore;

	/* These are interrupts we'll toggle with the ring mask register */
	u32 gt_interrupts[] = {
		(GT_RENDER_USER_INTERRUPT << GEN8_RCS_IRQ_SHIFT |
		 GT_CONTEXT_SWITCH_INTERRUPT << GEN8_RCS_IRQ_SHIFT |
		 GT_RENDER_USER_INTERRUPT << GEN8_BCS_IRQ_SHIFT |
		 GT_CONTEXT_SWITCH_INTERRUPT << GEN8_BCS_IRQ_SHIFT),

		(GT_RENDER_USER_INTERRUPT << GEN8_VCS0_IRQ_SHIFT |
		 GT_CONTEXT_SWITCH_INTERRUPT << GEN8_VCS0_IRQ_SHIFT |
		 GT_RENDER_USER_INTERRUPT << GEN8_VCS1_IRQ_SHIFT |
		 GT_CONTEXT_SWITCH_INTERRUPT << GEN8_VCS1_IRQ_SHIFT),

		0,

		(GT_RENDER_USER_INTERRUPT << GEN8_VECS_IRQ_SHIFT |
		 GT_CONTEXT_SWITCH_INTERRUPT << GEN8_VECS_IRQ_SHIFT)
	};

	gt->pm_ier = 0x0;
	gt->pm_imr = ~gt->pm_ier;
	GEN8_IRQ_INIT_NDX(uncore, GT, 0, ~gt_interrupts[0], gt_interrupts[0]);
	GEN8_IRQ_INIT_NDX(uncore, GT, 1, ~gt_interrupts[1], gt_interrupts[1]);
	/*
	 * RPS interrupts will get enabled/disabled on demand when RPS itself
	 * is enabled/disabled. Same wil be the case for GuC interrupts.
	 */
	GEN8_IRQ_INIT_NDX(uncore, GT, 2, gt->pm_imr, gt->pm_ier);
	GEN8_IRQ_INIT_NDX(uncore, GT, 3, ~gt_interrupts[3], gt_interrupts[3]);
}