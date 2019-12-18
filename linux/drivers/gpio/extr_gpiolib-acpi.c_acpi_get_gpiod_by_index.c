#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gpio_desc {int dummy; } ;
struct TYPE_2__ {struct acpi_device* adev; } ;
struct acpi_gpio_lookup {int index; struct gpio_desc* desc; TYPE_1__ info; int /*<<< orphan*/  active_low; int /*<<< orphan*/  pin_index; } ;
struct acpi_gpio_info {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  lookup ;

/* Variables and functions */
 int ENODEV ; 
 struct gpio_desc* ERR_PTR (int) ; 
 int /*<<< orphan*/  acpi_fwnode_handle (struct acpi_device*) ; 
 int acpi_gpio_property_lookup (int /*<<< orphan*/ ,char const*,int,struct acpi_gpio_lookup*) ; 
 int acpi_gpio_resource_lookup (struct acpi_gpio_lookup*,struct acpi_gpio_info*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct acpi_gpio_lookup*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct gpio_desc *acpi_get_gpiod_by_index(struct acpi_device *adev,
					  const char *propname, int index,
					  struct acpi_gpio_info *info)
{
	struct acpi_gpio_lookup lookup;
	int ret;

	if (!adev)
		return ERR_PTR(-ENODEV);

	memset(&lookup, 0, sizeof(lookup));
	lookup.index = index;

	if (propname) {
		dev_dbg(&adev->dev, "GPIO: looking up %s\n", propname);

		ret = acpi_gpio_property_lookup(acpi_fwnode_handle(adev),
						propname, index, &lookup);
		if (ret)
			return ERR_PTR(ret);

		dev_dbg(&adev->dev, "GPIO: _DSD returned %s %d %d %u\n",
			dev_name(&lookup.info.adev->dev), lookup.index,
			lookup.pin_index, lookup.active_low);
	} else {
		dev_dbg(&adev->dev, "GPIO: looking up %d in _CRS\n", index);
		lookup.info.adev = adev;
	}

	ret = acpi_gpio_resource_lookup(&lookup, info);
	return ret ? ERR_PTR(ret) : lookup.desc;
}