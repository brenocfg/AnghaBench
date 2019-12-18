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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ ngpio; } ;
struct lp_gpio {int /*<<< orphan*/  lock; TYPE_1__ chip; } ;
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INT_INV_BIT ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 int /*<<< orphan*/  LP_CONFIG1 ; 
 scalar_t__ TRIG_SEL_BIT ; 
 struct lp_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ inl (unsigned long) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 scalar_t__ irqd_to_hwirq (struct irq_data*) ; 
 unsigned long lp_gpio_reg (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int lp_irq_type(struct irq_data *d, unsigned type)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct lp_gpio *lg = gpiochip_get_data(gc);
	u32 hwirq = irqd_to_hwirq(d);
	unsigned long flags;
	u32 value;
	unsigned long reg = lp_gpio_reg(&lg->chip, hwirq, LP_CONFIG1);

	if (hwirq >= lg->chip.ngpio)
		return -EINVAL;

	spin_lock_irqsave(&lg->lock, flags);
	value = inl(reg);

	/* set both TRIG_SEL and INV bits to 0 for rising edge */
	if (type & IRQ_TYPE_EDGE_RISING)
		value &= ~(TRIG_SEL_BIT | INT_INV_BIT);

	/* TRIG_SEL bit 0, INV bit 1 for falling edge */
	if (type & IRQ_TYPE_EDGE_FALLING)
		value = (value | INT_INV_BIT) & ~TRIG_SEL_BIT;

	/* TRIG_SEL bit 1, INV bit 0 for level low */
	if (type & IRQ_TYPE_LEVEL_LOW)
		value = (value | TRIG_SEL_BIT) & ~INT_INV_BIT;

	/* TRIG_SEL bit 1, INV bit 1 for level high */
	if (type & IRQ_TYPE_LEVEL_HIGH)
		value |= TRIG_SEL_BIT | INT_INV_BIT;

	outl(value, reg);
	spin_unlock_irqrestore(&lg->lock, flags);

	return 0;
}