#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* clear_intr_status_nolock ) (struct dpu_hw_intr*,int) ;} ;
struct dpu_hw_intr {int* save_irq_status; int /*<<< orphan*/  irq_lock; TYPE_1__ ops; } ;
struct TYPE_6__ {int irq_mask; int reg_idx; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 TYPE_2__* dpu_intr_set ; 
 TYPE_2__* dpu_irq_map ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct dpu_hw_intr*,int) ; 

__attribute__((used)) static void dpu_hw_intr_dispatch_irq(struct dpu_hw_intr *intr,
		void (*cbfunc)(void *, int),
		void *arg)
{
	int reg_idx;
	int irq_idx;
	int start_idx;
	int end_idx;
	u32 irq_status;
	unsigned long irq_flags;

	if (!intr)
		return;

	/*
	 * The dispatcher will save the IRQ status before calling here.
	 * Now need to go through each IRQ status and find matching
	 * irq lookup index.
	 */
	spin_lock_irqsave(&intr->irq_lock, irq_flags);
	for (reg_idx = 0; reg_idx < ARRAY_SIZE(dpu_intr_set); reg_idx++) {
		irq_status = intr->save_irq_status[reg_idx];

		/*
		 * Each Interrupt register has a range of 32 indexes, and
		 * that is static for dpu_irq_map.
		 */
		start_idx = reg_idx * 32;
		end_idx = start_idx + 32;

		if (start_idx >= ARRAY_SIZE(dpu_irq_map) ||
				end_idx > ARRAY_SIZE(dpu_irq_map))
			continue;

		/*
		 * Search through matching intr status from irq map.
		 * start_idx and end_idx defined the search range in
		 * the dpu_irq_map.
		 */
		for (irq_idx = start_idx;
				(irq_idx < end_idx) && irq_status;
				irq_idx++)
			if ((irq_status & dpu_irq_map[irq_idx].irq_mask) &&
				(dpu_irq_map[irq_idx].reg_idx == reg_idx)) {
				/*
				 * Once a match on irq mask, perform a callback
				 * to the given cbfunc. cbfunc will take care
				 * the interrupt status clearing. If cbfunc is
				 * not provided, then the interrupt clearing
				 * is here.
				 */
				if (cbfunc)
					cbfunc(arg, irq_idx);
				else
					intr->ops.clear_intr_status_nolock(
							intr, irq_idx);

				/*
				 * When callback finish, clear the irq_status
				 * with the matching mask. Once irq_status
				 * is all cleared, the search can be stopped.
				 */
				irq_status &= ~dpu_irq_map[irq_idx].irq_mask;
			}
	}
	spin_unlock_irqrestore(&intr->irq_lock, irq_flags);
}