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
typedef  int /*<<< orphan*/  u32 ;
struct zynq_gpio {scalar_t__ base_addr; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 scalar_t__ ZYNQ_GPIO_DIRM_OFFSET (unsigned int) ; 
 scalar_t__ ZYNQ_GPIO_OUTEN_OFFSET (unsigned int) ; 
 struct zynq_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zynq_gpio_get_bank_pin (unsigned int,unsigned int*,unsigned int*,struct zynq_gpio*) ; 
 int /*<<< orphan*/  zynq_gpio_set_value (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int zynq_gpio_dir_out(struct gpio_chip *chip, unsigned int pin,
			     int state)
{
	u32 reg;
	unsigned int bank_num, bank_pin_num;
	struct zynq_gpio *gpio = gpiochip_get_data(chip);

	zynq_gpio_get_bank_pin(pin, &bank_num, &bank_pin_num, gpio);

	/* set the GPIO pin as output */
	reg = readl_relaxed(gpio->base_addr + ZYNQ_GPIO_DIRM_OFFSET(bank_num));
	reg |= BIT(bank_pin_num);
	writel_relaxed(reg, gpio->base_addr + ZYNQ_GPIO_DIRM_OFFSET(bank_num));

	/* configure the output enable reg for the pin */
	reg = readl_relaxed(gpio->base_addr + ZYNQ_GPIO_OUTEN_OFFSET(bank_num));
	reg |= BIT(bank_pin_num);
	writel_relaxed(reg, gpio->base_addr + ZYNQ_GPIO_OUTEN_OFFSET(bank_num));

	/* set the state of the pin */
	zynq_gpio_set_value(chip, pin, state);
	return 0;
}