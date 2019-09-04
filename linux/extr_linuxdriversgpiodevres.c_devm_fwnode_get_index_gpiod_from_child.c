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
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  prop_name ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct gpio_desc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  devm_gpiod_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct gpio_desc**) ; 
 struct gpio_desc** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct gpio_desc**) ; 
 struct gpio_desc* fwnode_get_named_gpiod (struct fwnode_handle*,char*,int,int,char const*) ; 
 char** gpio_suffixes ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

struct gpio_desc *devm_fwnode_get_index_gpiod_from_child(struct device *dev,
						const char *con_id, int index,
						struct fwnode_handle *child,
						enum gpiod_flags flags,
						const char *label)
{
	char prop_name[32]; /* 32 is max size of property name */
	struct gpio_desc **dr;
	struct gpio_desc *desc;
	unsigned int i;

	dr = devres_alloc(devm_gpiod_release, sizeof(struct gpio_desc *),
			  GFP_KERNEL);
	if (!dr)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < ARRAY_SIZE(gpio_suffixes); i++) {
		if (con_id)
			snprintf(prop_name, sizeof(prop_name), "%s-%s",
					    con_id, gpio_suffixes[i]);
		else
			snprintf(prop_name, sizeof(prop_name), "%s",
					    gpio_suffixes[i]);

		desc = fwnode_get_named_gpiod(child, prop_name, index, flags,
					      label);
		if (!IS_ERR(desc) || (PTR_ERR(desc) != -ENOENT))
			break;
	}
	if (IS_ERR(desc)) {
		devres_free(dr);
		return desc;
	}

	*dr = desc;
	devres_add(dev, dr);

	return desc;
}