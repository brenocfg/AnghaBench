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
struct device {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_usb_device (struct device*) ; 
 scalar_t__ is_usb_port (struct device*) ; 
 int /*<<< orphan*/  to_usb_device (struct device*) ; 
 int /*<<< orphan*/  to_usb_port (struct device*) ; 
 struct acpi_device* usb_acpi_find_companion_for_device (int /*<<< orphan*/ ) ; 
 struct acpi_device* usb_acpi_find_companion_for_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct acpi_device *usb_acpi_find_companion(struct device *dev)
{
	/*
	 * The USB hierarchy like following:
	 *
	 * Device (EHC1)
	 *	Device (HUBN)
	 *		Device (PR01)
	 *			Device (PR11)
	 *			Device (PR12)
	 *				Device (FN12)
	 *				Device (FN13)
	 *			Device (PR13)
	 *			...
	 * where HUBN is root hub, and PRNN are USB ports and devices
	 * connected to them, and FNNN are individualk functions for
	 * connected composite USB devices. PRNN and FNNN may contain
	 * _CRS and other methods describing sideband resources for
	 * the connected device.
	 *
	 * On the kernel side both root hub and embedded USB devices are
	 * represented as instances of usb_device structure, and ports
	 * are represented as usb_port structures, so the whole process
	 * is split into 2 parts: finding companions for devices and
	 * finding companions for ports.
	 *
	 * Note that we do not handle individual functions of composite
	 * devices yet, for that we would need to assign companions to
	 * devices corresponding to USB interfaces.
	 */
	if (is_usb_device(dev))
		return usb_acpi_find_companion_for_device(to_usb_device(dev));
	else if (is_usb_port(dev))
		return usb_acpi_find_companion_for_port(to_usb_port(dev));

	return NULL;
}