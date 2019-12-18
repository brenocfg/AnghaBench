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
struct devres {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOD_FLAGS_BIT_NONEXCLUSIVE ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  devm_gpiod_match ; 
 int /*<<< orphan*/  devm_gpiod_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct gpio_desc**) ; 
 struct gpio_desc** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct devres* devres_find (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpio_desc**) ; 
 struct gpio_desc* gpiod_get_from_of_node (struct device_node*,char const*,int,int,char const*) ; 
 int /*<<< orphan*/  gpiod_put (struct gpio_desc*) ; 

struct gpio_desc *devm_gpiod_get_from_of_node(struct device *dev,
					      struct device_node *node,
					      const char *propname, int index,
					      enum gpiod_flags dflags,
					      const char *label)
{
	struct gpio_desc **dr;
	struct gpio_desc *desc;

	desc = gpiod_get_from_of_node(node, propname, index, dflags, label);
	if (IS_ERR(desc))
		return desc;

	/*
	 * For non-exclusive GPIO descriptors, check if this descriptor is
	 * already under resource management by this device.
	 */
	if (dflags & GPIOD_FLAGS_BIT_NONEXCLUSIVE) {
		struct devres *dres;

		dres = devres_find(dev, devm_gpiod_release,
				   devm_gpiod_match, &desc);
		if (dres)
			return desc;
	}

	dr = devres_alloc(devm_gpiod_release, sizeof(struct gpio_desc *),
			  GFP_KERNEL);
	if (!dr) {
		gpiod_put(desc);
		return ERR_PTR(-ENOMEM);
	}

	*dr = desc;
	devres_add(dev, dr);

	return desc;
}