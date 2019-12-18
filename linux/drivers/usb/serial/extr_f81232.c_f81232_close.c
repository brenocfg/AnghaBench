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
struct usb_serial_port {int /*<<< orphan*/  interrupt_in_urb; } ;
struct f81232_private {int /*<<< orphan*/  lsr_work; int /*<<< orphan*/  interrupt_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  f81232_port_disable (struct usb_serial_port*) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct f81232_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_serial_generic_close (struct usb_serial_port*) ; 

__attribute__((used)) static void f81232_close(struct usb_serial_port *port)
{
	struct f81232_private *port_priv = usb_get_serial_port_data(port);

	f81232_port_disable(port);
	usb_serial_generic_close(port);
	usb_kill_urb(port->interrupt_in_urb);
	flush_work(&port_priv->interrupt_work);
	flush_work(&port_priv->lsr_work);
}