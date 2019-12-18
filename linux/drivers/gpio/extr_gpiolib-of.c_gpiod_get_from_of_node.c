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
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int EBUSY ; 
 struct gpio_desc* ERR_PTR (int) ; 
 int GPIOD_FLAGS_BIT_NONEXCLUSIVE ; 
 unsigned long GPIO_ACTIVE_LOW ; 
 unsigned long GPIO_LOOKUP_FLAGS_DEFAULT ; 
 unsigned long GPIO_OPEN_DRAIN ; 
 unsigned long GPIO_OPEN_SOURCE ; 
 unsigned long GPIO_TRANSITORY ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int OF_GPIO_ACTIVE_LOW ; 
 int OF_GPIO_OPEN_DRAIN ; 
 int OF_GPIO_SINGLE_ENDED ; 
 int OF_GPIO_TRANSITORY ; 
 int gpiod_configure_flags (struct gpio_desc*,char const*,unsigned long,int) ; 
 int /*<<< orphan*/  gpiod_put (struct gpio_desc*) ; 
 int gpiod_request (struct gpio_desc*,char const*) ; 
 struct gpio_desc* of_get_named_gpiod_flags (struct device_node*,char const*,int,int*) ; 

struct gpio_desc *gpiod_get_from_of_node(struct device_node *node,
					 const char *propname, int index,
					 enum gpiod_flags dflags,
					 const char *label)
{
	unsigned long lflags = GPIO_LOOKUP_FLAGS_DEFAULT;
	struct gpio_desc *desc;
	enum of_gpio_flags flags;
	bool active_low = false;
	bool single_ended = false;
	bool open_drain = false;
	bool transitory = false;
	int ret;

	desc = of_get_named_gpiod_flags(node, propname,
					index, &flags);

	if (!desc || IS_ERR(desc)) {
		return desc;
	}

	active_low = flags & OF_GPIO_ACTIVE_LOW;
	single_ended = flags & OF_GPIO_SINGLE_ENDED;
	open_drain = flags & OF_GPIO_OPEN_DRAIN;
	transitory = flags & OF_GPIO_TRANSITORY;

	ret = gpiod_request(desc, label);
	if (ret == -EBUSY && (dflags & GPIOD_FLAGS_BIT_NONEXCLUSIVE))
		return desc;
	if (ret)
		return ERR_PTR(ret);

	if (active_low)
		lflags |= GPIO_ACTIVE_LOW;

	if (single_ended) {
		if (open_drain)
			lflags |= GPIO_OPEN_DRAIN;
		else
			lflags |= GPIO_OPEN_SOURCE;
	}

	if (transitory)
		lflags |= GPIO_TRANSITORY;

	ret = gpiod_configure_flags(desc, propname, lflags, dflags);
	if (ret < 0) {
		gpiod_put(desc);
		return ERR_PTR(ret);
	}

	return desc;
}