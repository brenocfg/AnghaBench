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
struct TYPE_2__ {int /*<<< orphan*/  ttl_in0_7; int /*<<< orphan*/  ttl_out0_7; int /*<<< orphan*/  ctl; int /*<<< orphan*/  in16_23; int /*<<< orphan*/  in8_15; int /*<<< orphan*/  in0_7; int /*<<< orphan*/  out16_23; int /*<<< orphan*/  out8_15; int /*<<< orphan*/  out0_7; } ;

/* Variables and functions */
 unsigned long BIT (int) ; 
 struct idio_24_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned long const ioread8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idio_24_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct idio_24_gpio *const idio24gpio = gpiochip_get_data(chip);
	const unsigned long offset_mask = BIT(offset % 8);
	const unsigned long out_mode_mask = BIT(1);

	/* FET Outputs */
	if (offset < 8)
		return !!(ioread8(&idio24gpio->reg->out0_7) & offset_mask);

	if (offset < 16)
		return !!(ioread8(&idio24gpio->reg->out8_15) & offset_mask);

	if (offset < 24)
		return !!(ioread8(&idio24gpio->reg->out16_23) & offset_mask);

	/* Isolated Inputs */
	if (offset < 32)
		return !!(ioread8(&idio24gpio->reg->in0_7) & offset_mask);

	if (offset < 40)
		return !!(ioread8(&idio24gpio->reg->in8_15) & offset_mask);

	if (offset < 48)
		return !!(ioread8(&idio24gpio->reg->in16_23) & offset_mask);

	/* TTL/CMOS Outputs */
	if (ioread8(&idio24gpio->reg->ctl) & out_mode_mask)
		return !!(ioread8(&idio24gpio->reg->ttl_out0_7) & offset_mask);

	/* TTL/CMOS Inputs */
	return !!(ioread8(&idio24gpio->reg->ttl_in0_7) & offset_mask);
}