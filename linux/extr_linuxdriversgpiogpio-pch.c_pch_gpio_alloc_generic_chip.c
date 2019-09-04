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
struct pch_gpio {int /*<<< orphan*/  dev; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; } ;
struct irq_chip_type {TYPE_1__ chip; } ;
struct irq_chip_generic {struct irq_chip_type* chip_types; struct pch_gpio* private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQ_GC_INIT_MASK_CACHE ; 
 int /*<<< orphan*/  IRQ_MSK (unsigned int) ; 
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 struct irq_chip_generic* devm_irq_alloc_generic_chip (int /*<<< orphan*/ ,char*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_irq_setup_generic_chip (int /*<<< orphan*/ ,struct irq_chip_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  pch_irq_ack ; 
 int /*<<< orphan*/  pch_irq_mask ; 
 int /*<<< orphan*/  pch_irq_type ; 
 int /*<<< orphan*/  pch_irq_unmask ; 

__attribute__((used)) static int pch_gpio_alloc_generic_chip(struct pch_gpio *chip,
				       unsigned int irq_start,
				       unsigned int num)
{
	struct irq_chip_generic *gc;
	struct irq_chip_type *ct;
	int rv;

	gc = devm_irq_alloc_generic_chip(chip->dev, "pch_gpio", 1, irq_start,
					 chip->base, handle_simple_irq);
	if (!gc)
		return -ENOMEM;

	gc->private = chip;
	ct = gc->chip_types;

	ct->chip.irq_ack = pch_irq_ack;
	ct->chip.irq_mask = pch_irq_mask;
	ct->chip.irq_unmask = pch_irq_unmask;
	ct->chip.irq_set_type = pch_irq_type;

	rv = devm_irq_setup_generic_chip(chip->dev, gc, IRQ_MSK(num),
					 IRQ_GC_INIT_MASK_CACHE,
					 IRQ_NOREQUEST | IRQ_NOPROBE, 0);

	return rv;
}