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
struct list_head {int dummy; } ;
struct acpi_gpio_info {struct acpi_device* adev; } ;
struct acpi_gpio_lookup {struct acpi_gpio_info info; int /*<<< orphan*/  desc; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  acpi_dev_free_resource_list (struct list_head*) ; 
 int acpi_dev_get_resources (struct acpi_device*,struct list_head*,int /*<<< orphan*/ ,struct acpi_gpio_lookup*) ; 
 int /*<<< orphan*/  acpi_populate_gpio_lookup ; 

__attribute__((used)) static int acpi_gpio_resource_lookup(struct acpi_gpio_lookup *lookup,
				     struct acpi_gpio_info *info)
{
	struct acpi_device *adev = lookup->info.adev;
	struct list_head res_list;
	int ret;

	INIT_LIST_HEAD(&res_list);

	ret = acpi_dev_get_resources(adev, &res_list,
				     acpi_populate_gpio_lookup,
				     lookup);
	if (ret < 0)
		return ret;

	acpi_dev_free_resource_list(&res_list);

	if (!lookup->desc)
		return -ENOENT;

	if (info)
		*info = lookup->info;
	return 0;
}