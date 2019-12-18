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
typedef  unsigned int u32 ;
struct zynq_gpio {scalar_t__ base_addr; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ ZYNQ_GPIO_DATA_OFFSET (unsigned int) ; 
 scalar_t__ ZYNQ_GPIO_DATA_RO_OFFSET (unsigned int) ; 
 scalar_t__ gpio_data_ro_bug (struct zynq_gpio*) ; 
 struct zynq_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  zynq_gpio_get_bank_pin (unsigned int,unsigned int*,unsigned int*,struct zynq_gpio*) ; 
 scalar_t__ zynq_gpio_is_zynq (struct zynq_gpio*) ; 

__attribute__((used)) static int zynq_gpio_get_value(struct gpio_chip *chip, unsigned int pin)
{
	u32 data;
	unsigned int bank_num, bank_pin_num;
	struct zynq_gpio *gpio = gpiochip_get_data(chip);

	zynq_gpio_get_bank_pin(pin, &bank_num, &bank_pin_num, gpio);

	if (gpio_data_ro_bug(gpio)) {
		if (zynq_gpio_is_zynq(gpio)) {
			if (bank_num <= 1) {
				data = readl_relaxed(gpio->base_addr +
					ZYNQ_GPIO_DATA_RO_OFFSET(bank_num));
			} else {
				data = readl_relaxed(gpio->base_addr +
					ZYNQ_GPIO_DATA_OFFSET(bank_num));
			}
		} else {
			if (bank_num <= 2) {
				data = readl_relaxed(gpio->base_addr +
					ZYNQ_GPIO_DATA_RO_OFFSET(bank_num));
			} else {
				data = readl_relaxed(gpio->base_addr +
					ZYNQ_GPIO_DATA_OFFSET(bank_num));
			}
		}
	} else {
		data = readl_relaxed(gpio->base_addr +
			ZYNQ_GPIO_DATA_RO_OFFSET(bank_num));
	}
	return (data >> bank_pin_num) & 1;
}