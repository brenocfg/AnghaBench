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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tpic2810_set_mask_bits (struct gpio_chip*,unsigned long,unsigned long) ; 

__attribute__((used)) static void tpic2810_set_multiple(struct gpio_chip *chip, unsigned long *mask,
				  unsigned long *bits)
{
	tpic2810_set_mask_bits(chip, *mask, *bits);
}