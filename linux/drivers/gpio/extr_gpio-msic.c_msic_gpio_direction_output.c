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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int MSIC_GPIO_DIR_MASK ; 
 int MSIC_GPIO_DIR_OUT ; 
 unsigned int MSIC_GPIO_DOUT_MASK ; 
 int intel_msic_reg_update (int,int,unsigned int) ; 
 int msic_gpio_to_oreg (unsigned int) ; 

__attribute__((used)) static int msic_gpio_direction_output(struct gpio_chip *chip,
			unsigned offset, int value)
{
	int reg;
	unsigned mask;

	value = (!!value) | MSIC_GPIO_DIR_OUT;
	mask = MSIC_GPIO_DIR_MASK | MSIC_GPIO_DOUT_MASK;

	reg = msic_gpio_to_oreg(offset);
	if (reg < 0)
		return reg;

	return intel_msic_reg_update(reg, value, mask);
}