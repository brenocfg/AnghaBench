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
struct irq_data {size_t hwirq; } ;
struct gpio_chip {int dummy; } ;
struct gb_gpio_line {int masked; int masked_pending; } ;
struct gb_gpio_controller {struct gb_gpio_line* lines; } ;

/* Variables and functions */
 struct gb_gpio_controller* gpio_chip_to_gb_gpio_controller (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_to_gpio_chip (struct irq_data*) ; 

__attribute__((used)) static void gb_gpio_irq_mask(struct irq_data *d)
{
	struct gpio_chip *chip = irq_data_to_gpio_chip(d);
	struct gb_gpio_controller *ggc = gpio_chip_to_gb_gpio_controller(chip);
	struct gb_gpio_line *line = &ggc->lines[d->hwirq];

	line->masked = true;
	line->masked_pending = true;
}