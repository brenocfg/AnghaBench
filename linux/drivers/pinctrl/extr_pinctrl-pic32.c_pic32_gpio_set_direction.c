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
struct pinctrl_gpio_range {struct gpio_chip* gc; } ;
struct pinctrl_dev {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pic32_gpio_direction_input (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  pic32_gpio_direction_output (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pic32_gpio_set_direction(struct pinctrl_dev *pctldev,
					      struct pinctrl_gpio_range *range,
					      unsigned offset, bool input)
{
	struct gpio_chip *chip = range->gc;

	if (input)
		pic32_gpio_direction_input(chip, offset);
	else
		pic32_gpio_direction_output(chip, offset, 0);

	return 0;
}