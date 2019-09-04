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
struct gpio_chip {int /*<<< orphan*/  reg_clr; int /*<<< orphan*/  (* write_reg ) (int /*<<< orphan*/ ,unsigned long) ;int /*<<< orphan*/  reg_set; } ;

/* Variables and functions */
 unsigned long bgpio_line2mask (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void bgpio_set_with_clear(struct gpio_chip *gc, unsigned int gpio,
				 int val)
{
	unsigned long mask = bgpio_line2mask(gc, gpio);

	if (val)
		gc->write_reg(gc->reg_set, mask);
	else
		gc->write_reg(gc->reg_clr, mask);
}