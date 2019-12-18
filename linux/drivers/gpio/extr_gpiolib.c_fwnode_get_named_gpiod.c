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
struct acpi_gpio_info {int dummy; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct gpio_desc* ERR_PTR (int) ; 
 unsigned long GPIO_LOOKUP_FLAGS_DEFAULT ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  acpi_gpio_update_gpiod_flags (int*,struct acpi_gpio_info*) ; 
 int /*<<< orphan*/  acpi_gpio_update_gpiod_lookup_flags (unsigned long*,struct acpi_gpio_info*) ; 
 struct gpio_desc* acpi_node_get_gpiod (struct fwnode_handle*,char const*,int,struct acpi_gpio_info*) ; 
 int gpiod_configure_flags (struct gpio_desc*,char const*,unsigned long,int) ; 
 struct gpio_desc* gpiod_get_from_of_node (int /*<<< orphan*/ ,char const*,int,int,char const*) ; 
 int /*<<< orphan*/  gpiod_put (struct gpio_desc*) ; 
 int gpiod_request (struct gpio_desc*,char const*) ; 
 scalar_t__ is_acpi_node (struct fwnode_handle*) ; 
 scalar_t__ is_of_node (struct fwnode_handle*) ; 
 int /*<<< orphan*/  to_of_node (struct fwnode_handle*) ; 

struct gpio_desc *fwnode_get_named_gpiod(struct fwnode_handle *fwnode,
					 const char *propname, int index,
					 enum gpiod_flags dflags,
					 const char *label)
{
	unsigned long lflags = GPIO_LOOKUP_FLAGS_DEFAULT;
	struct gpio_desc *desc = ERR_PTR(-ENODEV);
	int ret;

	if (!fwnode)
		return ERR_PTR(-EINVAL);

	if (is_of_node(fwnode)) {
		desc = gpiod_get_from_of_node(to_of_node(fwnode),
					      propname, index,
					      dflags,
					      label);
		return desc;
	} else if (is_acpi_node(fwnode)) {
		struct acpi_gpio_info info;

		desc = acpi_node_get_gpiod(fwnode, propname, index, &info);
		if (IS_ERR(desc))
			return desc;

		acpi_gpio_update_gpiod_flags(&dflags, &info);
		acpi_gpio_update_gpiod_lookup_flags(&lflags, &info);
	}

	/* Currently only ACPI takes this path */
	ret = gpiod_request(desc, label);
	if (ret)
		return ERR_PTR(ret);

	ret = gpiod_configure_flags(desc, propname, lflags, dflags);
	if (ret < 0) {
		gpiod_put(desc);
		return ERR_PTR(ret);
	}

	return desc;
}