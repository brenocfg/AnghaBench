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
struct usb_serial_port {TYPE_1__* read_urb; TYPE_2__* write_urb; struct usb_serial* serial; } ;
struct usb_serial {int /*<<< orphan*/  dev; } ;
struct tty_struct {int dummy; } ;
struct spcp8x5_private {int /*<<< orphan*/  line_control; } ;
struct TYPE_4__ {int /*<<< orphan*/  pipe; } ;
struct TYPE_3__ {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  spcp8x5_set_ctrl_line (struct usb_serial_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spcp8x5_set_termios (struct tty_struct*,struct usb_serial_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 struct spcp8x5_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int usb_serial_generic_open (struct tty_struct*,struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spcp8x5_open(struct tty_struct *tty, struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;
	struct spcp8x5_private *priv = usb_get_serial_port_data(port);
	int ret;

	usb_clear_halt(serial->dev, port->write_urb->pipe);
	usb_clear_halt(serial->dev, port->read_urb->pipe);

	ret = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			      0x09, 0x00,
			      0x01, 0x00, NULL, 0x00, 100);
	if (ret)
		return ret;

	spcp8x5_set_ctrl_line(port, priv->line_control);

	if (tty)
		spcp8x5_set_termios(tty, port, NULL);

	return usb_serial_generic_open(tty, port);
}