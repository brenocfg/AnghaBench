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
struct usb_port {int location; int /*<<< orphan*/  connect_type; } ;
struct acpi_pld_info {int group_token; int group_position; } ;
struct acpi_device {int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_pld_info*) ; 
 int USB_ACPI_LOCATION_VALID ; 
 int /*<<< orphan*/  acpi_get_physical_device_location (int /*<<< orphan*/ *,struct acpi_pld_info**) ; 
 struct acpi_device* usb_acpi_get_companion_for_port (struct usb_port*) ; 
 int /*<<< orphan*/  usb_acpi_get_connect_type (int /*<<< orphan*/ *,struct acpi_pld_info*) ; 

__attribute__((used)) static struct acpi_device *
usb_acpi_find_companion_for_port(struct usb_port *port_dev)
{
	struct acpi_device *adev;
	struct acpi_pld_info *pld;
	acpi_handle *handle;
	acpi_status status;

	adev = usb_acpi_get_companion_for_port(port_dev);
	if (!adev)
		return NULL;

	handle = adev->handle;
	status = acpi_get_physical_device_location(handle, &pld);
	if (!ACPI_FAILURE(status) && pld) {
		port_dev->location = USB_ACPI_LOCATION_VALID
			| pld->group_token << 8 | pld->group_position;
		port_dev->connect_type = usb_acpi_get_connect_type(handle, pld);
		ACPI_FREE(pld);
	}

	return adev;
}