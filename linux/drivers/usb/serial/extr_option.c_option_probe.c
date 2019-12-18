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
struct usb_serial {TYPE_2__* interface; } ;
struct usb_interface_descriptor {scalar_t__ bInterfaceClass; int bNumEndpoints; int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_device_id {unsigned long driver_info; } ;
struct TYPE_4__ {TYPE_1__* cur_altsetting; } ;
struct TYPE_3__ {struct usb_interface_descriptor desc; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned long NUMEP2 ; 
 unsigned long RSVD (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_CLASS_MASS_STORAGE ; 
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,void*) ; 

__attribute__((used)) static int option_probe(struct usb_serial *serial,
			const struct usb_device_id *id)
{
	struct usb_interface_descriptor *iface_desc =
				&serial->interface->cur_altsetting->desc;
	unsigned long device_flags = id->driver_info;

	/* Never bind to the CD-Rom emulation interface	*/
	if (iface_desc->bInterfaceClass == USB_CLASS_MASS_STORAGE)
		return -ENODEV;

	/*
	 * Don't bind reserved interfaces (like network ones) which often have
	 * the same class/subclass/protocol as the serial interfaces.  Look at
	 * the Windows driver .INF files for reserved interface numbers.
	 */
	if (device_flags & RSVD(iface_desc->bInterfaceNumber))
		return -ENODEV;

	/*
	 * Allow matching on bNumEndpoints for devices whose interface numbers
	 * can change (e.g. Quectel EP06).
	 */
	if (device_flags & NUMEP2 && iface_desc->bNumEndpoints != 2)
		return -ENODEV;

	/* Store the device flags so we can use them during attach. */
	usb_set_serial_data(serial, (void *)device_flags);

	return 0;
}