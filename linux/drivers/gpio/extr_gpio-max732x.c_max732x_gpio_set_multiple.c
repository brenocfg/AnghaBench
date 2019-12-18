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
 int /*<<< orphan*/  max732x_gpio_set_mask (struct gpio_chip*,int,unsigned int,unsigned long) ; 

__attribute__((used)) static void max732x_gpio_set_multiple(struct gpio_chip *gc,
				      unsigned long *mask, unsigned long *bits)
{
	unsigned mask_lo = mask[0] & 0xff;
	unsigned mask_hi = (mask[0] >> 8) & 0xff;

	if (mask_lo)
		max732x_gpio_set_mask(gc, 0, mask_lo, bits[0] & 0xff);
	if (mask_hi)
		max732x_gpio_set_mask(gc, 8, mask_hi, (bits[0] >> 8) & 0xff);
}