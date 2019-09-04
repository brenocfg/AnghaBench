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
struct acpi_gpio_lookup {int index; struct gpio_desc* desc; } ;
struct acpi_gpio_info {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  lookup ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct gpio_desc* ERR_PTR (int) ; 
 struct gpio_desc* acpi_get_gpiod_by_index (struct acpi_device*,char const*,int,struct acpi_gpio_info*) ; 
 int acpi_gpio_property_lookup (struct fwnode_handle*,char const*,int,struct acpi_gpio_lookup*) ; 
 int acpi_gpio_resource_lookup (struct acpi_gpio_lookup*,struct acpi_gpio_info*) ; 
 int /*<<< orphan*/  is_acpi_data_node (struct fwnode_handle*) ; 
 int /*<<< orphan*/  memset (struct acpi_gpio_lookup*,int /*<<< orphan*/ ,int) ; 
 struct acpi_device* to_acpi_device_node (struct fwnode_handle*) ; 

struct gpio_desc *acpi_node_get_gpiod(struct fwnode_handle *fwnode,
				      const char *propname, int index,
				      struct acpi_gpio_info *info)
{
	struct acpi_gpio_lookup lookup;
	struct acpi_device *adev;
	int ret;

	adev = to_acpi_device_node(fwnode);
	if (adev)
		return acpi_get_gpiod_by_index(adev, propname, index, info);

	if (!is_acpi_data_node(fwnode))
		return ERR_PTR(-ENODEV);

	if (!propname)
		return ERR_PTR(-EINVAL);

	memset(&lookup, 0, sizeof(lookup));
	lookup.index = index;

	ret = acpi_gpio_property_lookup(fwnode, propname, index, &lookup);
	if (ret)
		return ERR_PTR(ret);

	ret = acpi_gpio_resource_lookup(&lookup, info);
	return ret ? ERR_PTR(ret) : lookup.desc;
}