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
typedef  scalar_t__ u16 ;
struct usb_serial_endpoints {int /*<<< orphan*/ * bulk_out; int /*<<< orphan*/ * bulk_in; } ;
struct usb_serial {TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  idProduct; } ;
struct TYPE_4__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 scalar_t__ MOSCHIP_DEVICE_ID_7715 ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mos77xx_calc_num_ports(struct usb_serial *serial,
					struct usb_serial_endpoints *epds)
{
	u16 product = le16_to_cpu(serial->dev->descriptor.idProduct);

	if (product == MOSCHIP_DEVICE_ID_7715) {
		/*
		 * The 7715 uses the first bulk in/out endpoint pair for the
		 * parallel port, and the second for the serial port. We swap
		 * the endpoint descriptors here so that the the first and
		 * only registered port structure uses the serial-port
		 * endpoints.
		 */
		swap(epds->bulk_in[0], epds->bulk_in[1]);
		swap(epds->bulk_out[0], epds->bulk_out[1]);

		return 1;
	}

	return 2;
}