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
struct acpi_driver {int dummy; } ;

/* Variables and functions */
 int acpi_bus_register_driver (struct acpi_driver*) ; 
 scalar_t__ acpi_disabled ; 

__attribute__((used)) static int acpi_button_register_driver(struct acpi_driver *driver)
{
	/*
	 * Modules such as nouveau.ko and i915.ko have a link time dependency
	 * on acpi_lid_open(), and would therefore not be loadable on ACPI
	 * capable kernels booted in non-ACPI mode if the return value of
	 * acpi_bus_register_driver() is returned from here with ACPI disabled
	 * when this driver is built as a module.
	 */
	if (acpi_disabled)
		return 0;

	return acpi_bus_register_driver(driver);
}