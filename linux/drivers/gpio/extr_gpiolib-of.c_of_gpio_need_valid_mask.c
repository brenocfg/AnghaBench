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
struct gpio_chip {struct device_node* of_node; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_count_u32_elems (struct device_node*,char*) ; 

bool of_gpio_need_valid_mask(const struct gpio_chip *gc)
{
	int size;
	struct device_node *np = gc->of_node;

	size = of_property_count_u32_elems(np,  "gpio-reserved-ranges");
	if (size > 0 && size % 2 == 0)
		return true;
	return false;
}