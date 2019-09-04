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
struct dpu_irq_type {int reg_idx; int irq_mask; } ;
struct dpu_intr_reg {int /*<<< orphan*/  en_off; int /*<<< orphan*/  clr_off; } ;
struct dpu_hw_intr {int* cache_irq_mask; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dpu_irq_type*) ; 
 int /*<<< orphan*/  DPU_REG_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int EINVAL ; 
 struct dpu_intr_reg* dpu_intr_set ; 
 struct dpu_irq_type* dpu_irq_map ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int dpu_hw_intr_enable_irq(struct dpu_hw_intr *intr, int irq_idx)
{
	int reg_idx;
	unsigned long irq_flags;
	const struct dpu_intr_reg *reg;
	const struct dpu_irq_type *irq;
	const char *dbgstr = NULL;
	uint32_t cache_irq_mask;

	if (!intr)
		return -EINVAL;

	if (irq_idx < 0 || irq_idx >= ARRAY_SIZE(dpu_irq_map)) {
		pr_err("invalid IRQ index: [%d]\n", irq_idx);
		return -EINVAL;
	}

	irq = &dpu_irq_map[irq_idx];
	reg_idx = irq->reg_idx;
	reg = &dpu_intr_set[reg_idx];

	spin_lock_irqsave(&intr->irq_lock, irq_flags);
	cache_irq_mask = intr->cache_irq_mask[reg_idx];
	if (cache_irq_mask & irq->irq_mask) {
		dbgstr = "DPU IRQ already set:";
	} else {
		dbgstr = "DPU IRQ enabled:";

		cache_irq_mask |= irq->irq_mask;
		/* Cleaning any pending interrupt */
		DPU_REG_WRITE(&intr->hw, reg->clr_off, irq->irq_mask);
		/* Enabling interrupts with the new mask */
		DPU_REG_WRITE(&intr->hw, reg->en_off, cache_irq_mask);

		/* ensure register write goes through */
		wmb();

		intr->cache_irq_mask[reg_idx] = cache_irq_mask;
	}
	spin_unlock_irqrestore(&intr->irq_lock, irq_flags);

	pr_debug("%s MASK:0x%.8x, CACHE-MASK:0x%.8x\n", dbgstr,
			irq->irq_mask, cache_irq_mask);

	return 0;
}