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
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable; int /*<<< orphan*/  disable; int /*<<< orphan*/  mask; } ;
struct irq_chip_type {TYPE_1__ regs; } ;
struct irq_chip_generic {int /*<<< orphan*/  wake_active; struct brcmstb_l2_intc_data* private; } ;
struct brcmstb_l2_intc_data {scalar_t__ can_wake; int /*<<< orphan*/  saved_mask; } ;

/* Variables and functions */
 struct irq_chip_type* irq_data_get_chip_type (struct irq_data*) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_gc_lock_irqsave (struct irq_chip_generic*,unsigned long) ; 
 int /*<<< orphan*/  irq_gc_unlock_irqrestore (struct irq_chip_generic*,unsigned long) ; 
 int /*<<< orphan*/  irq_reg_readl (struct irq_chip_generic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_reg_writel (struct irq_chip_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmstb_l2_intc_suspend(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct irq_chip_type *ct = irq_data_get_chip_type(d);
	struct brcmstb_l2_intc_data *b = gc->private;
	unsigned long flags;

	irq_gc_lock_irqsave(gc, flags);
	/* Save the current mask */
	b->saved_mask = irq_reg_readl(gc, ct->regs.mask);

	if (b->can_wake) {
		/* Program the wakeup mask */
		irq_reg_writel(gc, ~gc->wake_active, ct->regs.disable);
		irq_reg_writel(gc, gc->wake_active, ct->regs.enable);
	}
	irq_gc_unlock_irqrestore(gc, flags);
}