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
struct stx104_gpio {unsigned long out_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct stx104_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  outb (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void stx104_gpio_set_multiple(struct gpio_chip *chip,
	unsigned long *mask, unsigned long *bits)
{
	struct stx104_gpio *const stx104gpio = gpiochip_get_data(chip);
	unsigned long flags;

	/* verify masked GPIO are output */
	if (!(*mask & 0xF0))
		return;

	*mask >>= 4;
	*bits >>= 4;

	spin_lock_irqsave(&stx104gpio->lock, flags);

	stx104gpio->out_state &= ~*mask;
	stx104gpio->out_state |= *mask & *bits;
	outb(stx104gpio->out_state, stx104gpio->base);

	spin_unlock_irqrestore(&stx104gpio->lock, flags);
}