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
 scalar_t__ DM355EVM_MSP_LED ; 
 int EINVAL ; 
 int MSP_GPIO_MASK (unsigned int) ; 
 scalar_t__ MSP_GPIO_REG (unsigned int) ; 
 int dm355evm_msp_write (int,scalar_t__) ; 
 int msp_led_cache ; 

__attribute__((used)) static int msp_gpio_out(struct gpio_chip *chip, unsigned offset, int value)
{
	int mask, bits;

	/* NOTE:  there are some other signals that could be
	 * packaged as output GPIOs, but they aren't as useful
	 * as the LEDs ... so for now we don't.
	 */
	if (MSP_GPIO_REG(offset) != DM355EVM_MSP_LED)
		return -EINVAL;

	mask = MSP_GPIO_MASK(offset);
	bits = msp_led_cache;

	bits &= ~mask;
	if (value)
		bits |= mask;
	msp_led_cache = bits;

	return dm355evm_msp_write(bits, DM355EVM_MSP_LED);
}