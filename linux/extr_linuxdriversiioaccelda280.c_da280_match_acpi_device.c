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
struct acpi_device_id {int /*<<< orphan*/  driver_data; } ;
typedef  enum da280_chipset { ____Placeholder_da280_chipset } da280_chipset ;
struct TYPE_2__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 int EINVAL ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 

__attribute__((used)) static enum da280_chipset da280_match_acpi_device(struct device *dev)
{
	const struct acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	if (!id)
		return -EINVAL;

	return (enum da280_chipset) id->driver_data;
}