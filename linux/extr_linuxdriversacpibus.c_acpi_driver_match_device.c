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
struct device_driver {int /*<<< orphan*/  of_match_table; int /*<<< orphan*/  acpi_match_table; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 int __acpi_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_companion_match (struct device*) ; 
 int acpi_of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool acpi_driver_match_device(struct device *dev,
			      const struct device_driver *drv)
{
	if (!drv->acpi_match_table)
		return acpi_of_match_device(ACPI_COMPANION(dev),
					    drv->of_match_table,
					    NULL);

	return __acpi_match_device(acpi_companion_match(dev),
				   drv->acpi_match_table, drv->of_match_table,
				   NULL, NULL);
}