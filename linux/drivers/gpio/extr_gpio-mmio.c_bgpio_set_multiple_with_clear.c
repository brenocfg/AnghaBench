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
 int /*<<< orphan*/  bgpio_multiple_get_masks (struct gpio_chip*,unsigned long*,unsigned long*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void bgpio_set_multiple_with_clear(struct gpio_chip *gc,
					  unsigned long *mask,
					  unsigned long *bits)
{
	unsigned long set_mask, clear_mask;

	bgpio_multiple_get_masks(gc, mask, bits, &set_mask, &clear_mask);

	if (set_mask)
		gc->write_reg(gc->reg_set, set_mask);
	if (clear_mask)
		gc->write_reg(gc->reg_clr, clear_mask);
}