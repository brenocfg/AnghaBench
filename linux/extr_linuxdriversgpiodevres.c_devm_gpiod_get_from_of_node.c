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
struct device {int dummy; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  devm_gpiod_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct gpio_desc**) ; 
 struct gpio_desc** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct gpio_desc**) ; 
 struct gpio_desc* gpiod_get_from_of_node (struct device_node*,char const*,int,int,char const*) ; 

struct gpio_desc *devm_gpiod_get_from_of_node(struct device *dev,
					      struct device_node *node,
					      const char *propname, int index,
					      enum gpiod_flags dflags,
					      const char *label)
{
	struct gpio_desc **dr;
	struct gpio_desc *desc;

	dr = devres_alloc(devm_gpiod_release, sizeof(struct gpio_desc *),
			  GFP_KERNEL);
	if (!dr)
		return ERR_PTR(-ENOMEM);

	desc = gpiod_get_from_of_node(node, propname, index, dflags, label);
	if (IS_ERR(desc)) {
		devres_free(dr);
		return desc;
	}

	*dr = desc;
	devres_add(dev, dr);

	return desc;
}