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
struct device_node {int dummy; } ;
typedef  enum of_gpio_flags { ____Placeholder_of_gpio_flags } of_gpio_flags ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int desc_to_gpio (struct gpio_desc*) ; 
 struct gpio_desc* of_get_named_gpiod_flags (struct device_node*,char const*,int,int*) ; 

int of_get_named_gpio_flags(struct device_node *np, const char *list_name,
			    int index, enum of_gpio_flags *flags)
{
	struct gpio_desc *desc;

	desc = of_get_named_gpiod_flags(np, list_name, index, flags);

	if (IS_ERR(desc))
		return PTR_ERR(desc);
	else
		return desc_to_gpio(desc);
}