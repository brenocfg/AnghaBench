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
struct stm32_gpio_bank {int dummy; } ;
struct pinctrl_gpio_range {int /*<<< orphan*/  gc; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 struct stm32_gpio_bank* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int stm32_gpio_pin (unsigned int) ; 
 int stm32_pmx_set_mode (struct stm32_gpio_bank*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_pmx_gpio_set_direction(struct pinctrl_dev *pctldev,
			struct pinctrl_gpio_range *range, unsigned gpio,
			bool input)
{
	struct stm32_gpio_bank *bank = gpiochip_get_data(range->gc);
	int pin = stm32_gpio_pin(gpio);

	return stm32_pmx_set_mode(bank, pin, !input, 0);
}