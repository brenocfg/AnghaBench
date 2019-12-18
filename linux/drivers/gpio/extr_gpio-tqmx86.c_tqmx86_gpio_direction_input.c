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
 int BIT (unsigned int) ; 
 int EINVAL ; 
 int TQMX86_DIR_INPUT_MASK ; 

__attribute__((used)) static int tqmx86_gpio_direction_input(struct gpio_chip *chip,
				       unsigned int offset)
{
	/* Direction cannot be changed. Validate is an input. */
	if (BIT(offset) & TQMX86_DIR_INPUT_MASK)
		return 0;
	else
		return -EINVAL;
}