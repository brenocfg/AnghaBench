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
struct usb_serial_endpoints {int num_bulk_in; int num_bulk_out; } ;
struct usb_serial {TYPE_1__* interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int MOSCHIP_DEVICE_ID_7843 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ usb_get_serial_data (struct usb_serial*) ; 

__attribute__((used)) static int mos7840_calc_num_ports(struct usb_serial *serial,
					struct usb_serial_endpoints *epds)
{
	int device_type = (unsigned long)usb_get_serial_data(serial);
	int num_ports;

	if (device_type == MOSCHIP_DEVICE_ID_7843)
		num_ports = 3;
	else
		num_ports = (device_type >> 4) & 0x000F;

	/*
	 * num_ports is currently never zero as device_type is one of
	 * MOSCHIP_DEVICE_ID_78{1,2,4}0.
	 */
	if (num_ports == 0)
		return -ENODEV;

	if (epds->num_bulk_in < num_ports || epds->num_bulk_out < num_ports) {
		dev_err(&serial->interface->dev, "missing endpoints\n");
		return -ENODEV;
	}

	return num_ports;
}