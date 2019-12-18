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
typedef  int u8 ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int MSIC_GPIO_DIN_MASK ; 
 int intel_msic_reg_read (int,int*) ; 
 int msic_gpio_to_ireg (unsigned int) ; 

__attribute__((used)) static int msic_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	u8 r;
	int ret;
	int reg;

	reg = msic_gpio_to_ireg(offset);
	if (reg < 0)
		return reg;

	ret = intel_msic_reg_read(reg, &r);
	if (ret < 0)
		return ret;

	return !!(r & MSIC_GPIO_DIN_MASK);
}