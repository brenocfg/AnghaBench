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
struct stm32_pinctrl_group {int /*<<< orphan*/  pin; } ;
struct stm32_pinctrl {int /*<<< orphan*/  dev; struct stm32_pinctrl_group* groups; } ;
struct stm32_gpio_bank {int dummy; } ;
struct pinctrl_gpio_range {int /*<<< orphan*/  gc; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct stm32_gpio_bank* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 struct stm32_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 struct pinctrl_gpio_range* pinctrl_find_gpio_range_from_pin (struct pinctrl_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_gpio_get_alt (unsigned int) ; 
 int /*<<< orphan*/  stm32_gpio_get_mode (unsigned int) ; 
 int stm32_gpio_pin (int /*<<< orphan*/ ) ; 
 int stm32_pctrl_is_function_valid (struct stm32_pinctrl*,int /*<<< orphan*/ ,unsigned int) ; 
 int stm32_pmx_set_mode (struct stm32_gpio_bank*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_pmx_set_mux(struct pinctrl_dev *pctldev,
			    unsigned function,
			    unsigned group)
{
	bool ret;
	struct stm32_pinctrl *pctl = pinctrl_dev_get_drvdata(pctldev);
	struct stm32_pinctrl_group *g = pctl->groups + group;
	struct pinctrl_gpio_range *range;
	struct stm32_gpio_bank *bank;
	u32 mode, alt;
	int pin;

	ret = stm32_pctrl_is_function_valid(pctl, g->pin, function);
	if (!ret) {
		dev_err(pctl->dev, "invalid function %d on group %d .\n",
				function, group);
		return -EINVAL;
	}

	range = pinctrl_find_gpio_range_from_pin(pctldev, g->pin);
	if (!range) {
		dev_err(pctl->dev, "No gpio range defined.\n");
		return -EINVAL;
	}

	bank = gpiochip_get_data(range->gc);
	pin = stm32_gpio_pin(g->pin);

	mode = stm32_gpio_get_mode(function);
	alt = stm32_gpio_get_alt(function);

	return stm32_pmx_set_mode(bank, pin, mode, alt);
}