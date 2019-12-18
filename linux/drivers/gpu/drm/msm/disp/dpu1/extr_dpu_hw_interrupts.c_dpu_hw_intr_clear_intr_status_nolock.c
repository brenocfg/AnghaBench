#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dpu_hw_intr {int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  clr_off; } ;
struct TYPE_3__ {int reg_idx; int /*<<< orphan*/  irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* dpu_intr_set ; 
 TYPE_1__* dpu_irq_map ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void dpu_hw_intr_clear_intr_status_nolock(struct dpu_hw_intr *intr,
		int irq_idx)
{
	int reg_idx;

	if (!intr)
		return;

	reg_idx = dpu_irq_map[irq_idx].reg_idx;
	DPU_REG_WRITE(&intr->hw, dpu_intr_set[reg_idx].clr_off,
			dpu_irq_map[irq_idx].irq_mask);

	/* ensure register writes go through */
	wmb();
}