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
struct usb_serial_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  interrupt_in_urb; int /*<<< orphan*/  port; } ;
struct usb_serial {struct usb_serial_port** port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ tty_port_initialized (int /*<<< orphan*/ *) ; 
 int usb_serial_generic_resume (struct usb_serial*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f81232_resume(struct usb_serial *serial)
{
	struct usb_serial_port *port = serial->port[0];
	int result;

	if (tty_port_initialized(&port->port)) {
		result = usb_submit_urb(port->interrupt_in_urb, GFP_NOIO);
		if (result) {
			dev_err(&port->dev, "submit interrupt urb failed: %d\n",
					result);
			return result;
		}
	}

	return usb_serial_generic_resume(serial);
}