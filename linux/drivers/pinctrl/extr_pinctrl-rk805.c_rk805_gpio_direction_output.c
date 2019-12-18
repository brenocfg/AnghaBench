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
struct gpio_chip {scalar_t__ base; } ;

/* Variables and functions */
 int pinctrl_gpio_direction_output (scalar_t__) ; 
 int /*<<< orphan*/  rk805_gpio_set (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int rk805_gpio_direction_output(struct gpio_chip *chip,
				       unsigned int offset, int value)
{
	rk805_gpio_set(chip, offset, value);
	return pinctrl_gpio_direction_output(chip->base + offset);
}