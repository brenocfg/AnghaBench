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
union acpi_object {scalar_t__ type; } ;
struct list_head {int dummy; } ;
struct device {int dummy; } ;
struct acpi_gpio_mapping {int size; scalar_t__ name; } ;
struct acpi_device {struct acpi_gpio_mapping* driver_gpios; } ;
typedef  int /*<<< orphan*/  propname ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 scalar_t__ ACPI_TYPE_LOCAL_REFERENCE ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 unsigned int ARRAY_SIZE (char**) ; 
 int ENOENT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  acpi_can_fallback_to_crs (struct acpi_device*,char const*) ; 
 int /*<<< orphan*/  acpi_dev_free_resource_list (struct list_head*) ; 
 int acpi_dev_get_property (struct acpi_device*,char*,int /*<<< orphan*/ ,union acpi_object const**) ; 
 int /*<<< orphan*/  acpi_dev_get_resources (struct acpi_device*,struct list_head*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  acpi_find_gpio_count ; 
 int acpi_gpio_package_count (union acpi_object const*) ; 
 char** gpio_suffixes ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 

int acpi_gpio_count(struct device *dev, const char *con_id)
{
	struct acpi_device *adev = ACPI_COMPANION(dev);
	const union acpi_object *obj;
	const struct acpi_gpio_mapping *gm;
	int count = -ENOENT;
	int ret;
	char propname[32];
	unsigned int i;

	/* Try first from _DSD */
	for (i = 0; i < ARRAY_SIZE(gpio_suffixes); i++) {
		if (con_id)
			snprintf(propname, sizeof(propname), "%s-%s",
				 con_id, gpio_suffixes[i]);
		else
			snprintf(propname, sizeof(propname), "%s",
				 gpio_suffixes[i]);

		ret = acpi_dev_get_property(adev, propname, ACPI_TYPE_ANY,
					    &obj);
		if (ret == 0) {
			if (obj->type == ACPI_TYPE_LOCAL_REFERENCE)
				count = 1;
			else if (obj->type == ACPI_TYPE_PACKAGE)
				count = acpi_gpio_package_count(obj);
		} else if (adev->driver_gpios) {
			for (gm = adev->driver_gpios; gm->name; gm++)
				if (strcmp(propname, gm->name) == 0) {
					count = gm->size;
					break;
				}
		}
		if (count > 0)
			break;
	}

	/* Then from plain _CRS GPIOs */
	if (count < 0) {
		struct list_head resource_list;
		unsigned int crs_count = 0;

		if (!acpi_can_fallback_to_crs(adev, con_id))
			return count;

		INIT_LIST_HEAD(&resource_list);
		acpi_dev_get_resources(adev, &resource_list,
				       acpi_find_gpio_count, &crs_count);
		acpi_dev_free_resource_list(&resource_list);
		if (crs_count > 0)
			count = crs_count;
	}
	return count ? count : -ENOENT;
}