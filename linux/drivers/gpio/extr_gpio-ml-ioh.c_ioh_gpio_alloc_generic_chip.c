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
struct TYPE_2__ {int /*<<< orphan*/  irq_enable; int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; } ;
struct irq_chip_type {TYPE_1__ chip; } ;
struct irq_chip_generic {struct irq_chip_type* chip_types; struct ioh_gpio* private; } ;
struct ioh_gpio {int /*<<< orphan*/  dev; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IRQ_GC_INIT_MASK_CACHE ; 
 int /*<<< orphan*/  IRQ_MSK (unsigned int) ; 
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 struct irq_chip_generic* devm_irq_alloc_generic_chip (int /*<<< orphan*/ ,char*,int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_irq_setup_generic_chip (int /*<<< orphan*/ ,struct irq_chip_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  ioh_irq_disable ; 
 int /*<<< orphan*/  ioh_irq_enable ; 
 int /*<<< orphan*/  ioh_irq_mask ; 
 int /*<<< orphan*/  ioh_irq_type ; 
 int /*<<< orphan*/  ioh_irq_unmask ; 

__attribute__((used)) static int ioh_gpio_alloc_generic_chip(struct ioh_gpio *chip,
				       unsigned int irq_start,
				       unsigned int num)
{
	struct irq_chip_generic *gc;
	struct irq_chip_type *ct;
	int rv;

	gc = devm_irq_alloc_generic_chip(chip->dev, "ioh_gpio", 1, irq_start,
					 chip->base, handle_simple_irq);
	if (!gc)
		return -ENOMEM;

	gc->private = chip;
	ct = gc->chip_types;

	ct->chip.irq_mask = ioh_irq_mask;
	ct->chip.irq_unmask = ioh_irq_unmask;
	ct->chip.irq_set_type = ioh_irq_type;
	ct->chip.irq_disable = ioh_irq_disable;
	ct->chip.irq_enable = ioh_irq_enable;

	rv = devm_irq_setup_generic_chip(chip->dev, gc, IRQ_MSK(num),
					 IRQ_GC_INIT_MASK_CACHE,
					 IRQ_NOREQUEST | IRQ_NOPROBE, 0);

	return rv;
}