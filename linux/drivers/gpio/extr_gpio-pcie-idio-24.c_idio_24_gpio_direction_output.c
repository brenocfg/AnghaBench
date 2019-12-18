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
struct idio_24_gpio {int /*<<< orphan*/  lock; TYPE_1__* reg; } ;
struct gpio_chip {int /*<<< orphan*/  (* set ) (struct gpio_chip*,unsigned int,int) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 unsigned long BIT (int) ; 
 struct idio_24_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned long const ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int idio_24_gpio_direction_output(struct gpio_chip *chip,
	unsigned int offset, int value)
{
	struct idio_24_gpio *const idio24gpio = gpiochip_get_data(chip);
	unsigned long flags;
	unsigned int ctl_state;
	const unsigned long out_mode_mask = BIT(1);

	/* TTL/CMOS I/O */
	if (offset > 47) {
		raw_spin_lock_irqsave(&idio24gpio->lock, flags);

		/* Set TTL/CMOS Output Mode */
		ctl_state = ioread8(&idio24gpio->reg->ctl) | out_mode_mask;
		iowrite8(ctl_state, &idio24gpio->reg->ctl);

		raw_spin_unlock_irqrestore(&idio24gpio->lock, flags);
	}

	chip->set(chip, offset, value);
	return 0;
}