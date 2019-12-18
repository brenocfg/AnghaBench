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
struct gpio_chip {int bgpio_bits; scalar_t__ be_bits; } ;

/* Variables and functions */
 unsigned long BIT (unsigned int) ; 

__attribute__((used)) static unsigned long bgpio_line2mask(struct gpio_chip *gc, unsigned int line)
{
	if (gc->be_bits)
		return BIT(gc->bgpio_bits - 1 - line);
	return BIT(line);
}