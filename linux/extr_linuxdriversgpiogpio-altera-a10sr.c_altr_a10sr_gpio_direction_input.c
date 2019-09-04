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
 unsigned int ALTR_A10SR_IN_VALID_RANGE_LO ; 
 unsigned int ALTR_A10SR_LED_VALID_SHIFT ; 
 int EINVAL ; 

__attribute__((used)) static int altr_a10sr_gpio_direction_input(struct gpio_chip *gc,
					   unsigned int nr)
{
	if (nr >= (ALTR_A10SR_IN_VALID_RANGE_LO - ALTR_A10SR_LED_VALID_SHIFT))
		return 0;
	return -EINVAL;
}