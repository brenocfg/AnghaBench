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
typedef  int u32 ;
struct lpc18xx_gpio_pin_ic {int /*<<< orphan*/  lock; } ;
struct irq_data {int /*<<< orphan*/  hwirq; struct lpc18xx_gpio_pin_ic* chip_data; } ;

/* Variables and functions */
 int IRQ_TYPE_EDGE_FALLING ; 
 int IRQ_TYPE_EDGE_RISING ; 
 int IRQ_TYPE_LEVEL_MASK ; 
 int /*<<< orphan*/  LPC18XX_GPIO_PIN_IC_SIENF ; 
 int /*<<< orphan*/  LPC18XX_GPIO_PIN_IC_SIENR ; 
 int /*<<< orphan*/  irq_chip_unmask_parent (struct irq_data*) ; 
 int irqd_get_trigger_type (struct irq_data*) ; 
 int /*<<< orphan*/  lpc18xx_gpio_pin_ic_set (struct lpc18xx_gpio_pin_ic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lpc18xx_gpio_pin_ic_unmask(struct irq_data *d)
{
	struct lpc18xx_gpio_pin_ic *ic = d->chip_data;
	u32 type = irqd_get_trigger_type(d);

	raw_spin_lock(&ic->lock);

	if (type & IRQ_TYPE_LEVEL_MASK || type & IRQ_TYPE_EDGE_RISING)
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_SIENR);

	if (type & IRQ_TYPE_EDGE_FALLING)
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_SIENF);

	raw_spin_unlock(&ic->lock);

	irq_chip_unmask_parent(d);
}