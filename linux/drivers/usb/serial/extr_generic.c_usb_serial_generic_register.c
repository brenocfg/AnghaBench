#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int match_flags; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;

/* Variables and functions */
 int USB_DEVICE_ID_MATCH_PRODUCT ; 
 int USB_DEVICE_ID_MATCH_VENDOR ; 
 TYPE_1__* generic_device_ids ; 
 int /*<<< orphan*/  product ; 
 int /*<<< orphan*/  serial_drivers ; 
 int usb_serial_register_drivers (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  vendor ; 

int usb_serial_generic_register(void)
{
	int retval = 0;

#ifdef CONFIG_USB_SERIAL_GENERIC
	generic_device_ids[0].idVendor = vendor;
	generic_device_ids[0].idProduct = product;
	generic_device_ids[0].match_flags =
		USB_DEVICE_ID_MATCH_VENDOR | USB_DEVICE_ID_MATCH_PRODUCT;

	retval = usb_serial_register_drivers(serial_drivers,
			"usbserial_generic", generic_device_ids);
#endif
	return retval;
}