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
struct gpio_chip {int ngpio; unsigned long (* read_reg ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  reg_dat; } ;

/* Variables and functions */
 unsigned long bgpio_line2mask (struct gpio_chip*,int) ; 
 int find_next_bit (unsigned long*,int,int) ; 
 unsigned long stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bgpio_get_multiple_be(struct gpio_chip *gc, unsigned long *mask,
				 unsigned long *bits)
{
	unsigned long readmask = 0;
	unsigned long val;
	int bit;

	/* Make sure we first clear any bits that are zero when we read the register */
	*bits &= ~*mask;

	/* Create a mirrored mask */
	bit = -1;
	while ((bit = find_next_bit(mask, gc->ngpio, bit + 1)) < gc->ngpio)
		readmask |= bgpio_line2mask(gc, bit);

	/* Read the register */
	val = gc->read_reg(gc->reg_dat) & readmask;

	/*
	 * Mirror the result into the "bits" result, this will give line 0
	 * in bit 0 ... line 31 in bit 31 for a 32bit register.
	 */
	bit = -1;
	while ((bit = find_next_bit(&val, gc->ngpio, bit + 1)) < gc->ngpio)
		*bits |= bgpio_line2mask(gc, bit);

	return 0;
}