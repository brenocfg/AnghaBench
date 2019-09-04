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
struct zynq_gpio {int /*<<< orphan*/  irq; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct zynq_gpio* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irq_set_irq_wake (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int zynq_gpio_set_wake(struct irq_data *data, unsigned int on)
{
	struct zynq_gpio *gpio =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	irq_set_irq_wake(gpio->irq, on);

	return 0;
}