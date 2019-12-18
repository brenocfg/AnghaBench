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
struct gpio_desc {int dummy; } ;
struct gpio_array {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  extra_checks ; 
 int gpiod_get_array_value_complex (int,int,unsigned int,struct gpio_desc**,struct gpio_array*,unsigned long*) ; 
 int /*<<< orphan*/  might_sleep_if (int /*<<< orphan*/ ) ; 

int gpiod_get_raw_array_value_cansleep(unsigned int array_size,
				       struct gpio_desc **desc_array,
				       struct gpio_array *array_info,
				       unsigned long *value_bitmap)
{
	might_sleep_if(extra_checks);
	if (!desc_array)
		return -EINVAL;
	return gpiod_get_array_value_complex(true, true, array_size,
					     desc_array, array_info,
					     value_bitmap);
}