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
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int acpi_device_set_power (struct acpi_device*,int) ; 

int acpi_bus_set_power(acpi_handle handle, int state)
{
	struct acpi_device *device;
	int result;

	result = acpi_bus_get_device(handle, &device);
	if (result)
		return result;

	return acpi_device_set_power(device, state);
}