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
struct gpio_chip {int (* read_reg ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  reg_dir; scalar_t__ bgpio_dir_inverted; } ;

/* Variables and functions */
 int bgpio_line2mask (struct gpio_chip*,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bgpio_get_dir(struct gpio_chip *gc, unsigned int gpio)
{
	/* Return 0 if output, 1 of input */
	if (gc->bgpio_dir_inverted)
		return !!(gc->read_reg(gc->reg_dir) & bgpio_line2mask(gc, gpio));
	else
		return !(gc->read_reg(gc->reg_dir) & bgpio_line2mask(gc, gpio));
}