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
struct device {TYPE_1__* driver; } ;
struct acpi_device_id {scalar_t__ driver_data; int /*<<< orphan*/  id; } ;
typedef  enum kx_chipset { ____Placeholder_kx_chipset } kx_chipset ;
struct TYPE_2__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 char const* dev_name (struct device*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const char *kxcjk1013_match_acpi_device(struct device *dev,
					       enum kx_chipset *chipset,
					       bool *is_smo8500_device)
{
	const struct acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	if (!id)
		return NULL;

	if (strcmp(id->id, "SMO8500") == 0)
		*is_smo8500_device = true;

	*chipset = (enum kx_chipset)id->driver_data;

	return dev_name(dev);
}