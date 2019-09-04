#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpio_chip {int dummy; } ;
struct TYPE_4__ {TYPE_1__* desc; } ;
struct TYPE_3__ {int* use_sel_ignore; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_USE_SEL ; 
 int /*<<< orphan*/  ichx_gpio_check_available (struct gpio_chip*,unsigned int) ; 
 TYPE_2__ ichx_priv ; 
 scalar_t__ ichx_read_bit (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ichx_gpio_request(struct gpio_chip *chip, unsigned nr)
{
	if (!ichx_gpio_check_available(chip, nr))
		return -ENXIO;

	/*
	 * Note we assume the BIOS properly set a bridge's USE value.  Some
	 * chips (eg Intel 3100) have bogus USE values though, so first see if
	 * the chipset's USE value can be trusted for this specific bit.
	 * If it can't be trusted, assume that the pin can be used as a GPIO.
	 */
	if (ichx_priv.desc->use_sel_ignore[nr / 32] & BIT(nr & 0x1f))
		return 0;

	return ichx_read_bit(GPIO_USE_SEL, nr) ? 0 : -ENODEV;
}