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
struct gpio_chip {unsigned long bgpio_data; int /*<<< orphan*/  bgpio_lock; int /*<<< orphan*/  reg_set; int /*<<< orphan*/  (* write_reg ) (int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 unsigned long bgpio_line2mask (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void bgpio_set_set(struct gpio_chip *gc, unsigned int gpio, int val)
{
	unsigned long mask = bgpio_line2mask(gc, gpio);
	unsigned long flags;

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	if (val)
		gc->bgpio_data |= mask;
	else
		gc->bgpio_data &= ~mask;

	gc->write_reg(gc->reg_set, gc->bgpio_data);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);
}