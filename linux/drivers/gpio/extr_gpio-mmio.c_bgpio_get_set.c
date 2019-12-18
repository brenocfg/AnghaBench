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
struct gpio_chip {unsigned long bgpio_dir; unsigned long (* read_reg ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  reg_dat; int /*<<< orphan*/  reg_set; } ;

/* Variables and functions */
 unsigned long bgpio_line2mask (struct gpio_chip*,unsigned int) ; 
 unsigned long stub1 (int /*<<< orphan*/ ) ; 
 unsigned long stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bgpio_get_set(struct gpio_chip *gc, unsigned int gpio)
{
	unsigned long pinmask = bgpio_line2mask(gc, gpio);
	bool dir = !!(gc->bgpio_dir & pinmask);

	if (dir)
		return !!(gc->read_reg(gc->reg_set) & pinmask);
	else
		return !!(gc->read_reg(gc->reg_dat) & pinmask);
}