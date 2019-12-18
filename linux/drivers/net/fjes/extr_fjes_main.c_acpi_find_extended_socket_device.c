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
 int /*<<< orphan*/  ACPI_MOTHERBOARD_RESOURCE_HID ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 int acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 scalar_t__ acpi_check_extended_socket_status (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_hid (struct acpi_device*) ; 
 int /*<<< orphan*/  is_extended_socket_device (struct acpi_device*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_find_extended_socket_device(acpi_handle obj_handle, u32 level,
				 void *context, void **return_value)
{
	struct acpi_device *device;
	bool *found = context;
	int result;

	result = acpi_bus_get_device(obj_handle, &device);
	if (result)
		return AE_OK;

	if (strcmp(acpi_device_hid(device), ACPI_MOTHERBOARD_RESOURCE_HID))
		return AE_OK;

	if (!is_extended_socket_device(device))
		return AE_OK;

	if (acpi_check_extended_socket_status(device))
		return AE_OK;

	*found = true;
	return AE_CTRL_TERMINATE;
}