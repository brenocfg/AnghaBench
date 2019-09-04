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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int ACPI_BUS_TYPE_POWER ; 
 int /*<<< orphan*/  AE_CTRL_DEPTH ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_add_power_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_add_single_object (struct acpi_device**,int /*<<< orphan*/ ,int,unsigned long long) ; 
 int /*<<< orphan*/  acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int acpi_bus_type_and_status (int /*<<< orphan*/ ,int*,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_device_dep_initialize (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_scan_init_hotplug (struct acpi_device*) ; 

__attribute__((used)) static acpi_status acpi_bus_check_add(acpi_handle handle, u32 lvl_not_used,
				      void *not_used, void **return_value)
{
	struct acpi_device *device = NULL;
	int type;
	unsigned long long sta;
	int result;

	acpi_bus_get_device(handle, &device);
	if (device)
		goto out;

	result = acpi_bus_type_and_status(handle, &type, &sta);
	if (result)
		return AE_OK;

	if (type == ACPI_BUS_TYPE_POWER) {
		acpi_add_power_resource(handle);
		return AE_OK;
	}

	acpi_add_single_object(&device, handle, type, sta);
	if (!device)
		return AE_CTRL_DEPTH;

	acpi_scan_init_hotplug(device);
	acpi_device_dep_initialize(device);

 out:
	if (!*return_value)
		*return_value = device;

	return AE_OK;
}