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
struct zynq_gpio {scalar_t__ base_addr; } ;
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 scalar_t__ ZYNQ_GPIO_INTEN_OFFSET (unsigned int) ; 
 struct zynq_gpio* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zynq_gpio_get_bank_pin (unsigned int,unsigned int*,unsigned int*,struct zynq_gpio*) ; 

__attribute__((used)) static void zynq_gpio_irq_unmask(struct irq_data *irq_data)
{
	unsigned int device_pin_num, bank_num, bank_pin_num;
	struct zynq_gpio *gpio =
		gpiochip_get_data(irq_data_get_irq_chip_data(irq_data));

	device_pin_num = irq_data->hwirq;
	zynq_gpio_get_bank_pin(device_pin_num, &bank_num, &bank_pin_num, gpio);
	writel_relaxed(BIT(bank_pin_num),
		       gpio->base_addr + ZYNQ_GPIO_INTEN_OFFSET(bank_num));
}