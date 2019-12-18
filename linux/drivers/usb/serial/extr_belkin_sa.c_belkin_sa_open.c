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
struct usb_serial_port {int /*<<< orphan*/  interrupt_in_urb; int /*<<< orphan*/  dev; } ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int usb_serial_generic_open (struct tty_struct*,struct usb_serial_port*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int belkin_sa_open(struct tty_struct *tty,
					struct usb_serial_port *port)
{
	int retval;

	retval = usb_submit_urb(port->interrupt_in_urb, GFP_KERNEL);
	if (retval) {
		dev_err(&port->dev, "usb_submit_urb(read int) failed\n");
		return retval;
	}

	retval = usb_serial_generic_open(tty, port);
	if (retval)
		usb_kill_urb(port->interrupt_in_urb);

	return retval;
}