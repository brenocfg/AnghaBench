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
struct irq_data {unsigned int hwirq; } ;
struct gpio_bank {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_clear_gpio_irqstatus (struct gpio_bank*,unsigned int) ; 
 struct gpio_bank* omap_irq_data_get_bank (struct irq_data*) ; 

__attribute__((used)) static void omap_gpio_ack_irq(struct irq_data *d)
{
	struct gpio_bank *bank = omap_irq_data_get_bank(d);
	unsigned offset = d->hwirq;

	omap_clear_gpio_irqstatus(bank, offset);
}