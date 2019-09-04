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
struct TYPE_2__ {int /*<<< orphan*/  irq_enable; int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  irq_set_type; } ;
struct irq_chip_type {int /*<<< orphan*/  handler; TYPE_1__ chip; } ;
struct irq_chip_generic {scalar_t__ irq_base; scalar_t__ irq_cnt; struct irq_chip_type* chip_types; struct gsta_gpio* private; } ;
struct gsta_gpio {int irq_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GSTA_NR_GPIO ; 
 int IRQ_NOPROBE ; 
 int IRQ_NOREQUEST ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 struct irq_chip_generic* devm_irq_alloc_generic_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_irq_setup_generic_chip (int /*<<< orphan*/ ,struct irq_chip_generic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsta_irq_disable ; 
 int /*<<< orphan*/  gsta_irq_enable ; 
 int /*<<< orphan*/  gsta_irq_type ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  irq_clear_status_flags (int,int) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (int,struct irq_chip_generic*) ; 

__attribute__((used)) static int gsta_alloc_irq_chip(struct gsta_gpio *chip)
{
	struct irq_chip_generic *gc;
	struct irq_chip_type *ct;
	int rv;

	gc = devm_irq_alloc_generic_chip(chip->dev, KBUILD_MODNAME, 1,
					 chip->irq_base,
					 chip->reg_base, handle_simple_irq);
	if (!gc)
		return -ENOMEM;

	gc->private = chip;
	ct = gc->chip_types;

	ct->chip.irq_set_type = gsta_irq_type;
	ct->chip.irq_disable = gsta_irq_disable;
	ct->chip.irq_enable = gsta_irq_enable;

	/* FIXME: this makes at most 32 interrupts. Request 0 by now */
	rv = devm_irq_setup_generic_chip(chip->dev, gc,
					 0 /* IRQ_MSK(GSTA_GPIO_PER_BLOCK) */,
					 0, IRQ_NOREQUEST | IRQ_NOPROBE, 0);
	if (rv)
		return rv;

	/* Set up all all 128 interrupts: code from setup_generic_chip */
	{
		struct irq_chip_type *ct = gc->chip_types;
		int i, j;
		for (j = 0; j < GSTA_NR_GPIO; j++) {
			i = chip->irq_base + j;
			irq_set_chip_and_handler(i, &ct->chip, ct->handler);
			irq_set_chip_data(i, gc);
			irq_clear_status_flags(i, IRQ_NOREQUEST | IRQ_NOPROBE);
		}
		gc->irq_cnt = i - gc->irq_base;
	}

	return 0;
}