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

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_array_value_complex (int,int,unsigned int,struct gpio_desc**,int*) ; 

void gpiod_set_array_value(unsigned int array_size,
			   struct gpio_desc **desc_array, int *value_array)
{
	if (!desc_array)
		return;
	gpiod_set_array_value_complex(false, false, array_size, desc_array,
				      value_array);
}