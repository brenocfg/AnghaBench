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
struct usb_serial_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  interrupt_in_urb; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyspan_pda_rx_unthrottle(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	/* just restart the receive interrupt URB */

	if (usb_submit_urb(port->interrupt_in_urb, GFP_KERNEL))
		dev_dbg(&port->dev, "usb_submit_urb(read urb) failed\n");
}