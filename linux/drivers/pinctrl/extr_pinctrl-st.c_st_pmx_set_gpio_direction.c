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
struct st_gpio_bank {int /*<<< orphan*/  pc; } ;
struct pinctrl_gpio_range {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_GPIO_DIRECTION_IN ; 
 int /*<<< orphan*/  ST_GPIO_DIRECTION_OUT ; 
 struct st_gpio_bank* gpio_range_to_bank (struct pinctrl_gpio_range*) ; 
 int /*<<< orphan*/  st_gpio_direction (struct st_gpio_bank*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_pctl_set_function (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_pmx_set_gpio_direction(struct pinctrl_dev *pctldev,
			struct pinctrl_gpio_range *range, unsigned gpio,
			bool input)
{
	struct st_gpio_bank *bank = gpio_range_to_bank(range);
	/*
	 * When a PIO bank is used in its primary function mode (altfunc = 0)
	 * Output Enable (OE), Open Drain(OD), and Pull Up (PU)
	 * for the primary PIO functions are driven by the related PIO block
	 */
	st_pctl_set_function(&bank->pc, gpio, 0);
	st_gpio_direction(bank, gpio, input ?
		ST_GPIO_DIRECTION_IN : ST_GPIO_DIRECTION_OUT);

	return 0;
}