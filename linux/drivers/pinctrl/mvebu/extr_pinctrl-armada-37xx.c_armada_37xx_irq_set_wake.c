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
typedef  scalar_t__ u32 ;
struct irq_data {int hwirq; } ;
struct gpio_chip {int dummy; } ;
struct armada_37xx_pinctrl {int /*<<< orphan*/  irq_lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ BIT (int) ; 
 int GPIO_PER_REG ; 
 scalar_t__ IRQ_WKUP ; 
 int /*<<< orphan*/  armada_37xx_irq_update_reg (scalar_t__*,struct irq_data*) ; 
 struct armada_37xx_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int armada_37xx_irq_set_wake(struct irq_data *d, unsigned int on)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(d);
	struct armada_37xx_pinctrl *info = gpiochip_get_data(chip);
	u32 val, reg = IRQ_WKUP;
	unsigned long flags;

	armada_37xx_irq_update_reg(&reg, d);
	spin_lock_irqsave(&info->irq_lock, flags);
	val = readl(info->base + reg);
	if (on)
		val |= (BIT(d->hwirq % GPIO_PER_REG));
	else
		val &= ~(BIT(d->hwirq % GPIO_PER_REG));
	writel(val, info->base + reg);
	spin_unlock_irqrestore(&info->irq_lock, flags);

	return 0;
}