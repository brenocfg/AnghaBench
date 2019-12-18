#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct idio_24_gpio {TYPE_1__* reg; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 unsigned long BIT (int) ; 
 struct idio_24_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned long const ioread8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idio_24_gpio_get_direction(struct gpio_chip *chip,
	unsigned int offset)
{
	struct idio_24_gpio *const idio24gpio = gpiochip_get_data(chip);
	const unsigned long out_mode_mask = BIT(1);

	/* FET Outputs */
	if (offset < 24)
		return 0;

	/* Isolated Inputs */
	if (offset < 48)
		return 1;

	/* TTL/CMOS I/O */
	/* OUT MODE = 1 when TTL/CMOS Output Mode is set */
	return !(ioread8(&idio24gpio->reg->ctl) & out_mode_mask);
}