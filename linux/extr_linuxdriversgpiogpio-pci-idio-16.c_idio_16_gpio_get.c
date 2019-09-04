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
struct idio_16_gpio {TYPE_1__* reg; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  in8_15; int /*<<< orphan*/  in0_7; int /*<<< orphan*/  out8_15; int /*<<< orphan*/  out0_7; } ;

/* Variables and functions */
 unsigned long BIT (unsigned int) ; 
 struct idio_16_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned long ioread8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idio_16_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct idio_16_gpio *const idio16gpio = gpiochip_get_data(chip);
	unsigned long mask = BIT(offset);

	if (offset < 8)
		return !!(ioread8(&idio16gpio->reg->out0_7) & mask);

	if (offset < 16)
		return !!(ioread8(&idio16gpio->reg->out8_15) & (mask >> 8));

	if (offset < 24)
		return !!(ioread8(&idio16gpio->reg->in0_7) & (mask >> 16));

	return !!(ioread8(&idio16gpio->reg->in8_15) & (mask >> 24));
}