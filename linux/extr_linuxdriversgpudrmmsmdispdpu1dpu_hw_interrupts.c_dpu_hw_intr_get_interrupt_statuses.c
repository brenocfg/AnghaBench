#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct dpu_hw_intr {int* save_irq_status; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  clr_off; int /*<<< orphan*/  en_off; int /*<<< orphan*/  status_off; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 void* DPU_REG_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* dpu_intr_set ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void dpu_hw_intr_get_interrupt_statuses(struct dpu_hw_intr *intr)
{
	int i;
	u32 enable_mask;
	unsigned long irq_flags;

	if (!intr)
		return;

	spin_lock_irqsave(&intr->irq_lock, irq_flags);
	for (i = 0; i < ARRAY_SIZE(dpu_intr_set); i++) {
		/* Read interrupt status */
		intr->save_irq_status[i] = DPU_REG_READ(&intr->hw,
				dpu_intr_set[i].status_off);

		/* Read enable mask */
		enable_mask = DPU_REG_READ(&intr->hw, dpu_intr_set[i].en_off);

		/* and clear the interrupt */
		if (intr->save_irq_status[i])
			DPU_REG_WRITE(&intr->hw, dpu_intr_set[i].clr_off,
					intr->save_irq_status[i]);

		/* Finally update IRQ status based on enable mask */
		intr->save_irq_status[i] &= enable_mask;
	}

	/* ensure register writes go through */
	wmb();

	spin_unlock_irqrestore(&intr->irq_lock, irq_flags);
}