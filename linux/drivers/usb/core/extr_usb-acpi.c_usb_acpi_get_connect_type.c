#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int count; TYPE_2__* elements; } ;
union acpi_object {scalar_t__ type; TYPE_3__ package; } ;
struct acpi_pld_info {scalar_t__ user_visible; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  enum usb_port_connect_type { ____Placeholder_usb_port_connect_type } usb_port_connect_type ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int USB_PORT_CONNECT_TYPE_HARD_WIRED ; 
 int USB_PORT_CONNECT_TYPE_HOT_PLUG ; 
 int USB_PORT_CONNECT_TYPE_UNKNOWN ; 
 int USB_PORT_NOT_USED ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

__attribute__((used)) static enum usb_port_connect_type usb_acpi_get_connect_type(acpi_handle handle,
		struct acpi_pld_info *pld)
{
	enum usb_port_connect_type connect_type = USB_PORT_CONNECT_TYPE_UNKNOWN;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *upc;
	acpi_status status;

	/*
	 * According to 9.14 in ACPI Spec 6.2. _PLD indicates whether usb port
	 * is user visible and _UPC indicates whether it is connectable. If
	 * the port was visible and connectable, it could be freely connected
	 * and disconnected with USB devices. If no visible and connectable,
	 * a usb device is directly hard-wired to the port. If no visible and
	 * no connectable, the port would be not used.
	 */
	status = acpi_evaluate_object(handle, "_UPC", NULL, &buffer);
	upc = buffer.pointer;
	if (!upc || (upc->type != ACPI_TYPE_PACKAGE)
		|| upc->package.count != 4) {
		goto out;
	}

	if (upc->package.elements[0].integer.value)
		if (pld->user_visible)
			connect_type = USB_PORT_CONNECT_TYPE_HOT_PLUG;
		else
			connect_type = USB_PORT_CONNECT_TYPE_HARD_WIRED;
	else if (!pld->user_visible)
		connect_type = USB_PORT_NOT_USED;
out:
	kfree(upc);
	return connect_type;
}