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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct irq_data {int /*<<< orphan*/  mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  disable; int /*<<< orphan*/  ack; } ;
struct irq_chip_type {TYPE_1__ regs; } ;
struct irq_chip_generic {struct regmap* private; } ;

/* Variables and functions */
 struct irq_chip_type* irq_data_get_chip_type (struct irq_data*) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_gc_lock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  irq_gc_unlock (struct irq_chip_generic*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ingenic_tcu_gc_mask_disable_reg_and_ack(struct irq_data *d)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct irq_chip_type *ct = irq_data_get_chip_type(d);
	struct regmap *map = gc->private;
	u32 mask = d->mask;

	irq_gc_lock(gc);
	regmap_write(map, ct->regs.ack, mask);
	regmap_write(map, ct->regs.disable, mask);
	irq_gc_unlock(gc);
}