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
struct usb_serial_port {int dummy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct serial_struct {int /*<<< orphan*/  custom_divisor; int /*<<< orphan*/  baud_base; int /*<<< orphan*/  flags; } ;
struct ftdi_private {int /*<<< orphan*/  custom_divisor; int /*<<< orphan*/  baud_base; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int get_serial_info(struct tty_struct *tty,
				struct serial_struct *ss)
{
	struct usb_serial_port *port = tty->driver_data;
	struct ftdi_private *priv = usb_get_serial_port_data(port);

	ss->flags = priv->flags;
	ss->baud_base = priv->baud_base;
	ss->custom_divisor = priv->custom_divisor;
	return 0;
}