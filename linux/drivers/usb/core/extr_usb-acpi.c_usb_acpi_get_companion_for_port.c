#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* parent; } ;
struct usb_port {int portnum; TYPE_2__ dev; } ;
struct usb_device {int /*<<< orphan*/  portnum; int /*<<< orphan*/  parent; int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_bus_get_device (int /*<<< orphan*/ *,struct acpi_device**) ; 
 int /*<<< orphan*/  bus_to_hcd (int /*<<< orphan*/ ) ; 
 struct usb_device* to_usb_device (int /*<<< orphan*/ ) ; 
 struct acpi_device* usb_acpi_find_port (struct acpi_device*,int) ; 
 int /*<<< orphan*/ * usb_get_hub_port_acpi_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_hcd_find_raw_port_number (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct acpi_device *
usb_acpi_get_companion_for_port(struct usb_port *port_dev)
{
	struct usb_device *udev;
	struct acpi_device *adev;
	acpi_handle *parent_handle;
	int port1;

	/* Get the struct usb_device point of port's hub */
	udev = to_usb_device(port_dev->dev.parent->parent);

	/*
	 * The root hub ports' parent is the root hub. The non-root-hub
	 * ports' parent is the parent hub port which the hub is
	 * connected to.
	 */
	if (!udev->parent) {
		adev = ACPI_COMPANION(&udev->dev);
		port1 = usb_hcd_find_raw_port_number(bus_to_hcd(udev->bus),
						     port_dev->portnum);
	} else {
		parent_handle = usb_get_hub_port_acpi_handle(udev->parent,
							     udev->portnum);
		if (!parent_handle)
			return NULL;

		acpi_bus_get_device(parent_handle, &adev);
		port1 = port_dev->portnum;
	}

	return usb_acpi_find_port(adev, port1);
}