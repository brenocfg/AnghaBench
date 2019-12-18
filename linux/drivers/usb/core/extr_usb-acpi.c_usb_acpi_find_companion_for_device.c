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
struct usb_port {int dummy; } ;
struct usb_hub {struct usb_port** ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct usb_device {int portnum; int /*<<< orphan*/  parent; TYPE_1__ dev; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ ) ; 
 struct acpi_device* acpi_find_child_device (struct acpi_device*,int /*<<< orphan*/ ,int) ; 
 struct acpi_device* usb_acpi_get_companion_for_port (struct usb_port*) ; 
 struct usb_hub* usb_hub_to_struct_hub (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct acpi_device *
usb_acpi_find_companion_for_device(struct usb_device *udev)
{
	struct acpi_device *adev;
	struct usb_port *port_dev;
	struct usb_hub *hub;

	if (!udev->parent) {
		/* root hub is only child (_ADR=0) under its parent, the HC */
		adev = ACPI_COMPANION(udev->dev.parent);
		return acpi_find_child_device(adev, 0, false);
	}

	hub = usb_hub_to_struct_hub(udev->parent);
	if (!hub)
		return NULL;

	/*
	 * This is an embedded USB device connected to a port and such
	 * devices share port's ACPI companion.
	 */
	port_dev = hub->ports[udev->portnum - 1];
	return usb_acpi_get_companion_for_port(port_dev);
}