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
 unsigned long stub1 (int /*<<< orphan*/ ) ; 
 unsigned long stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bgpio_get_set_multiple(struct gpio_chip *gc, unsigned long *mask,
				  unsigned long *bits)
{
	unsigned long get_mask = 0;
	unsigned long set_mask = 0;

	/* Make sure we first clear any bits that are zero when we read the register */
	*bits &= ~*mask;

	set_mask = *mask & gc->bgpio_dir;
	get_mask = *mask & ~gc->bgpio_dir;

	if (set_mask)
		*bits |= gc->read_reg(gc->reg_set) & set_mask;
	if (get_mask)
		*bits |= gc->read_reg(gc->reg_dat) & get_mask;

	return 0;
}