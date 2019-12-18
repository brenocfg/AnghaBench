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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct keyspan_serial_private {struct keyspan_device_details* device_details; } ;
struct keyspan_device_details {int msg_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  keyspan_usa26_send_setup (struct usb_serial*,struct usb_serial_port*,int) ; 
 int /*<<< orphan*/  keyspan_usa28_send_setup (struct usb_serial*,struct usb_serial_port*,int) ; 
 int /*<<< orphan*/  keyspan_usa49_send_setup (struct usb_serial*,struct usb_serial_port*,int) ; 
 int /*<<< orphan*/  keyspan_usa67_send_setup (struct usb_serial*,struct usb_serial_port*,int) ; 
 int /*<<< orphan*/  keyspan_usa90_send_setup (struct usb_serial*,struct usb_serial_port*,int) ; 
#define  msg_usa26 132 
#define  msg_usa28 131 
#define  msg_usa49 130 
#define  msg_usa67 129 
#define  msg_usa90 128 
 struct keyspan_serial_private* usb_get_serial_data (struct usb_serial*) ; 

__attribute__((used)) static void keyspan_send_setup(struct usb_serial_port *port, int reset_port)
{
	struct usb_serial *serial = port->serial;
	struct keyspan_serial_private *s_priv;
	const struct keyspan_device_details *d_details;

	s_priv = usb_get_serial_data(serial);
	d_details = s_priv->device_details;

	switch (d_details->msg_format) {
	case msg_usa26:
		keyspan_usa26_send_setup(serial, port, reset_port);
		break;
	case msg_usa28:
		keyspan_usa28_send_setup(serial, port, reset_port);
		break;
	case msg_usa49:
		keyspan_usa49_send_setup(serial, port, reset_port);
		break;
	case msg_usa90:
		keyspan_usa90_send_setup(serial, port, reset_port);
		break;
	case msg_usa67:
		keyspan_usa67_send_setup(serial, port, reset_port);
		break;
	}
}