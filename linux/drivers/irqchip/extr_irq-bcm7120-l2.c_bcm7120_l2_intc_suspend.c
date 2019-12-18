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
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;
struct irq_chip_type {TYPE_1__ regs; } ;
struct irq_chip_generic {int mask_cache; int wake_active; struct irq_chip_type* chip_types; struct bcm7120_l2_intc_data* private; } ;
struct bcm7120_l2_intc_data {scalar_t__ can_wake; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_gc_lock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_gc_unlock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_reg_writel (struct irq_chip_generic*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm7120_l2_intc_suspend(struct irq_chip_generic *gc)
{
	struct bcm7120_l2_intc_data *b = gc->private;
	struct irq_chip_type *ct = gc->chip_types;

	irq_gc_lock(gc);
	if (b->can_wake)
		irq_reg_writel(gc, gc->mask_cache | gc->wake_active,
			       ct->regs.mask);
	irq_gc_unlock(gc);
}