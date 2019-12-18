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
struct pl061 {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned char BIT (unsigned int) ; 
 scalar_t__ GPIODIR ; 
 struct pl061* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int pl061_direction_output(struct gpio_chip *gc, unsigned offset,
		int value)
{
	struct pl061 *pl061 = gpiochip_get_data(gc);
	unsigned long flags;
	unsigned char gpiodir;

	raw_spin_lock_irqsave(&pl061->lock, flags);
	writeb(!!value << offset, pl061->base + (BIT(offset + 2)));
	gpiodir = readb(pl061->base + GPIODIR);
	gpiodir |= BIT(offset);
	writeb(gpiodir, pl061->base + GPIODIR);

	/*
	 * gpio value is set again, because pl061 doesn't allow to set value of
	 * a gpio pin before configuring it in OUT mode.
	 */
	writeb(!!value << offset, pl061->base + (BIT(offset + 2)));
	raw_spin_unlock_irqrestore(&pl061->lock, flags);

	return 0;
}