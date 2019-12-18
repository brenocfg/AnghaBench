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
struct lpc18xx_gpio_pin_ic {int /*<<< orphan*/  lock; } ;
struct irq_data {int /*<<< orphan*/  hwirq; struct lpc18xx_gpio_pin_ic* chip_data; } ;

/* Variables and functions */
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 int /*<<< orphan*/  LPC18XX_GPIO_PIN_IC_CIENF ; 
 int /*<<< orphan*/  LPC18XX_GPIO_PIN_IC_SIENF ; 
 int /*<<< orphan*/  lpc18xx_gpio_pin_ic_isel (struct lpc18xx_gpio_pin_ic*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpc18xx_gpio_pin_ic_set (struct lpc18xx_gpio_pin_ic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc18xx_gpio_pin_ic_set_type(struct irq_data *d, unsigned int type)
{
	struct lpc18xx_gpio_pin_ic *ic = d->chip_data;

	raw_spin_lock(&ic->lock);

	if (type & IRQ_TYPE_LEVEL_HIGH) {
		lpc18xx_gpio_pin_ic_isel(ic, d->hwirq, true);
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_SIENF);
	} else if (type & IRQ_TYPE_LEVEL_LOW) {
		lpc18xx_gpio_pin_ic_isel(ic, d->hwirq, true);
		lpc18xx_gpio_pin_ic_set(ic, d->hwirq,
					LPC18XX_GPIO_PIN_IC_CIENF);
	} else {
		lpc18xx_gpio_pin_ic_isel(ic, d->hwirq, false);
	}

	raw_spin_unlock(&ic->lock);

	return 0;
}