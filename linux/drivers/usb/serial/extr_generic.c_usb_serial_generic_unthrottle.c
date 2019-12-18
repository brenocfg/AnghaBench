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
struct usb_serial_port {int /*<<< orphan*/  flags; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_SERIAL_THROTTLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  usb_serial_generic_submit_read_urbs (struct usb_serial_port*,int /*<<< orphan*/ ) ; 

void usb_serial_generic_unthrottle(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;

	clear_bit(USB_SERIAL_THROTTLED, &port->flags);

	/*
	 * Matches the smp_mb__after_atomic() in
	 * usb_serial_generic_read_bulk_callback().
	 */
	smp_mb();

	usb_serial_generic_submit_read_urbs(port, GFP_KERNEL);
}