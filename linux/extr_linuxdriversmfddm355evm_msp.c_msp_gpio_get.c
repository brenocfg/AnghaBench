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
 int DM355EVM_MSP_LED ; 
 int MSP_GPIO_MASK (unsigned int) ; 
 int MSP_GPIO_REG (unsigned int) ; 
 int dm355evm_msp_read (int) ; 
 int msp_led_cache ; 

__attribute__((used)) static int msp_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	int reg, status;

	reg = MSP_GPIO_REG(offset);
	status = dm355evm_msp_read(reg);
	if (status < 0)
		return status;
	if (reg == DM355EVM_MSP_LED)
		msp_led_cache = status;
	return !!(status & MSP_GPIO_MASK(offset));
}