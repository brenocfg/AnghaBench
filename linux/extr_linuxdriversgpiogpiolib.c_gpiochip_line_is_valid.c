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
struct gpio_chip {int /*<<< orphan*/  valid_mask; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int test_bit (unsigned int,int /*<<< orphan*/ ) ; 

bool gpiochip_line_is_valid(const struct gpio_chip *gpiochip,
				unsigned int offset)
{
	/* No mask means all valid */
	if (likely(!gpiochip->valid_mask))
		return true;
	return test_bit(offset, gpiochip->valid_mask);
}