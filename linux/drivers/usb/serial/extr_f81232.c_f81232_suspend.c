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
struct usb_serial_port {int /*<<< orphan*/  interrupt_in_urb; int /*<<< orphan*/ * read_urbs; } ;
struct usb_serial {struct usb_serial_port** port; } ;
struct f81232_private {int /*<<< orphan*/  lsr_work; int /*<<< orphan*/  interrupt_work; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct f81232_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f81232_suspend(struct usb_serial *serial, pm_message_t message)
{
	struct usb_serial_port *port = serial->port[0];
	struct f81232_private *port_priv = usb_get_serial_port_data(port);
	int i;

	for (i = 0; i < ARRAY_SIZE(port->read_urbs); ++i)
		usb_kill_urb(port->read_urbs[i]);

	usb_kill_urb(port->interrupt_in_urb);

	if (port_priv) {
		flush_work(&port_priv->interrupt_work);
		flush_work(&port_priv->lsr_work);
	}

	return 0;
}