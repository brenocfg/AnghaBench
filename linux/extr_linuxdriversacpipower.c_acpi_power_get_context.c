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
struct acpi_power_resource {int dummy; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 struct acpi_power_resource* to_power_resource (struct acpi_device*) ; 

__attribute__((used)) static struct acpi_power_resource *acpi_power_get_context(acpi_handle handle)
{
	struct acpi_device *device;

	if (acpi_bus_get_device(handle, &device))
		return NULL;

	return to_power_resource(device);
}