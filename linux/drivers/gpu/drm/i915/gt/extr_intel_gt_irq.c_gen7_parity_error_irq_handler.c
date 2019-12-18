#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct intel_gt {TYPE_2__* i915; int /*<<< orphan*/  irq_lock; } ;
struct TYPE_4__ {int which_slice; int /*<<< orphan*/  error_work; } ;
struct TYPE_5__ {TYPE_1__ l3_parity; } ;

/* Variables and functions */
 int /*<<< orphan*/  GT_PARITY_ERROR (TYPE_2__*) ; 
 int GT_RENDER_L3_PARITY_ERROR_INTERRUPT ; 
 int GT_RENDER_L3_PARITY_ERROR_INTERRUPT_S1 ; 
 int /*<<< orphan*/  HAS_L3_DPF (TYPE_2__*) ; 
 int /*<<< orphan*/  gen5_gt_disable_irq (struct intel_gt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen7_parity_error_irq_handler(struct intel_gt *gt, u32 iir)
{
	if (!HAS_L3_DPF(gt->i915))
		return;

	spin_lock(&gt->irq_lock);
	gen5_gt_disable_irq(gt, GT_PARITY_ERROR(gt->i915));
	spin_unlock(&gt->irq_lock);

	if (iir & GT_RENDER_L3_PARITY_ERROR_INTERRUPT_S1)
		gt->i915->l3_parity.which_slice |= 1 << 1;

	if (iir & GT_RENDER_L3_PARITY_ERROR_INTERRUPT)
		gt->i915->l3_parity.which_slice |= 1 << 0;

	schedule_work(&gt->i915->l3_parity.error_work);
}