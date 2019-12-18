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
struct stmpe_gpio {int** regs; TYPE_1__* stmpe; } ;
struct irq_data {int hwirq; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {scalar_t__ partnum; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 size_t REG_FE ; 
 size_t REG_RE ; 
 scalar_t__ STMPE1600 ; 
 scalar_t__ STMPE801 ; 
 struct stmpe_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int stmpe_gpio_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct stmpe_gpio *stmpe_gpio = gpiochip_get_data(gc);
	int offset = d->hwirq;
	int regoffset = offset / 8;
	int mask = BIT(offset % 8);

	if (type & IRQ_TYPE_LEVEL_LOW || type & IRQ_TYPE_LEVEL_HIGH)
		return -EINVAL;

	/* STMPE801 and STMPE 1600 don't have RE and FE registers */
	if (stmpe_gpio->stmpe->partnum == STMPE801 ||
	    stmpe_gpio->stmpe->partnum == STMPE1600)
		return 0;

	if (type & IRQ_TYPE_EDGE_RISING)
		stmpe_gpio->regs[REG_RE][regoffset] |= mask;
	else
		stmpe_gpio->regs[REG_RE][regoffset] &= ~mask;

	if (type & IRQ_TYPE_EDGE_FALLING)
		stmpe_gpio->regs[REG_FE][regoffset] |= mask;
	else
		stmpe_gpio->regs[REG_FE][regoffset] &= ~mask;

	return 0;
}