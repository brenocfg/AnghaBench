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
struct idio_16_gpio {int /*<<< orphan*/  lock; TYPE_1__* reg; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  out8_15; int /*<<< orphan*/  out0_7; } ;

/* Variables and functions */
 struct idio_16_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned long ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void idio_16_gpio_set_multiple(struct gpio_chip *chip,
	unsigned long *mask, unsigned long *bits)
{
	struct idio_16_gpio *const idio16gpio = gpiochip_get_data(chip);
	unsigned long flags;
	unsigned int out_state;

	raw_spin_lock_irqsave(&idio16gpio->lock, flags);

	/* process output lines 0-7 */
	if (*mask & 0xFF) {
		out_state = ioread8(&idio16gpio->reg->out0_7) & ~*mask;
		out_state |= *mask & *bits;
		iowrite8(out_state, &idio16gpio->reg->out0_7);
	}

	/* shift to next output line word */
	*mask >>= 8;

	/* process output lines 8-15 */
	if (*mask & 0xFF) {
		*bits >>= 8;
		out_state = ioread8(&idio16gpio->reg->out8_15) & ~*mask;
		out_state |= *mask & *bits;
		iowrite8(out_state, &idio16gpio->reg->out8_15);
	}

	raw_spin_unlock_irqrestore(&idio16gpio->lock, flags);
}