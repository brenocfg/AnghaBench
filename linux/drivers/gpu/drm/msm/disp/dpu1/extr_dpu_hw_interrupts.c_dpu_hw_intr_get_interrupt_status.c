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
struct dpu_hw_intr {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  clr_off; int /*<<< orphan*/  status_off; } ;
struct TYPE_4__ {int reg_idx; int irq_mask; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int DPU_REG_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* dpu_intr_set ; 
 TYPE_1__* dpu_irq_map ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static u32 dpu_hw_intr_get_interrupt_status(struct dpu_hw_intr *intr,
		int irq_idx, bool clear)
{
	int reg_idx;
	unsigned long irq_flags;
	u32 intr_status;

	if (!intr)
		return 0;

	if (irq_idx >= ARRAY_SIZE(dpu_irq_map) || irq_idx < 0) {
		pr_err("invalid IRQ index: [%d]\n", irq_idx);
		return 0;
	}

	spin_lock_irqsave(&intr->irq_lock, irq_flags);

	reg_idx = dpu_irq_map[irq_idx].reg_idx;
	intr_status = DPU_REG_READ(&intr->hw,
			dpu_intr_set[reg_idx].status_off) &
					dpu_irq_map[irq_idx].irq_mask;
	if (intr_status && clear)
		DPU_REG_WRITE(&intr->hw, dpu_intr_set[reg_idx].clr_off,
				intr_status);

	/* ensure register writes go through */
	wmb();

	spin_unlock_irqrestore(&intr->irq_lock, irq_flags);

	return intr_status;
}