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
struct usb_serial_port {int /*<<< orphan*/  port_number; TYPE_1__* read_urb; TYPE_1__* write_urb; struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct moschip_port {scalar_t__ open; TYPE_1__** write_urb_pool; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOS7720_IER ; 
 int /*<<< orphan*/  MOS7720_MCR ; 
 int NUM_URBS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 struct moschip_port* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  write_mos_reg (struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mos7720_close(struct usb_serial_port *port)
{
	struct usb_serial *serial;
	struct moschip_port *mos7720_port;
	int j;

	serial = port->serial;

	mos7720_port = usb_get_serial_port_data(port);
	if (mos7720_port == NULL)
		return;

	for (j = 0; j < NUM_URBS; ++j)
		usb_kill_urb(mos7720_port->write_urb_pool[j]);

	/* Freeing Write URBs */
	for (j = 0; j < NUM_URBS; ++j) {
		if (mos7720_port->write_urb_pool[j]) {
			kfree(mos7720_port->write_urb_pool[j]->transfer_buffer);
			usb_free_urb(mos7720_port->write_urb_pool[j]);
		}
	}

	/* While closing port, shutdown all bulk read, write  *
	 * and interrupt read if they exists, otherwise nop   */
	usb_kill_urb(port->write_urb);
	usb_kill_urb(port->read_urb);

	write_mos_reg(serial, port->port_number, MOS7720_MCR, 0x00);
	write_mos_reg(serial, port->port_number, MOS7720_IER, 0x00);

	mos7720_port->open = 0;
}