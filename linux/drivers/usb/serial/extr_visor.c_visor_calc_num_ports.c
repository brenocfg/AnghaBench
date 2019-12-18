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
struct usb_serial_endpoints {int num_interrupt_in; int num_bulk_in; int /*<<< orphan*/ * interrupt_in; int /*<<< orphan*/ * bulk_in; } ;
struct usb_serial {TYPE_3__* interface; TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  idVendor; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int HANDSPRING_VENDOR_ID ; 
 unsigned int KYOCERA_VENDOR_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_get_serial_data (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int visor_calc_num_ports(struct usb_serial *serial,
					struct usb_serial_endpoints *epds)
{
	unsigned int vid = le16_to_cpu(serial->dev->descriptor.idVendor);
	int num_ports = (int)(long)(usb_get_serial_data(serial));

	if (num_ports)
		usb_set_serial_data(serial, NULL);

	/*
	 * Only swap the bulk endpoints for the Handspring devices with
	 * interrupt in endpoints, which for now are the Treo devices.
	 */
	if (!(vid == HANDSPRING_VENDOR_ID || vid == KYOCERA_VENDOR_ID) ||
			epds->num_interrupt_in == 0)
		goto out;

	if (epds->num_bulk_in < 2 || epds->num_interrupt_in < 2) {
		dev_err(&serial->interface->dev, "missing endpoints\n");
		return -ENODEV;
	}

	/*
	 * It appears that Treos and Kyoceras want to use the
	 * 1st bulk in endpoint to communicate with the 2nd bulk out endpoint,
	 * so let's swap the 1st and 2nd bulk in and interrupt endpoints.
	 * Note that swapping the bulk out endpoints would break lots of
	 * apps that want to communicate on the second port.
	 */
	swap(epds->bulk_in[0], epds->bulk_in[1]);
	swap(epds->interrupt_in[0], epds->interrupt_in[1]);
out:
	return num_ports;
}