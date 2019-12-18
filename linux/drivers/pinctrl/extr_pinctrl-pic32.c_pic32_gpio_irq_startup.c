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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  pic32_gpio_direction_input (struct gpio_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic32_gpio_irq_unmask (struct irq_data*) ; 

__attribute__((used)) static unsigned int pic32_gpio_irq_startup(struct irq_data *data)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(data);

	pic32_gpio_direction_input(chip, data->hwirq);
	pic32_gpio_irq_unmask(data);

	return 0;
}