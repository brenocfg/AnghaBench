#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_port {int /*<<< orphan*/  dev; TYPE_1__* serial; } ;
struct ftdi_private {int /*<<< orphan*/  interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTDI_SIO_SET_FLOW_CTRL_REQUEST ; 
 int /*<<< orphan*/  FTDI_SIO_SET_FLOW_CTRL_REQUEST_TYPE ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  WDR_TIMEOUT ; 
 int /*<<< orphan*/  clear_mctrl (struct usb_serial_port*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_mctrl (struct usb_serial_port*,int) ; 
 scalar_t__ usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftdi_dtr_rts(struct usb_serial_port *port, int on)
{
	struct ftdi_private *priv = usb_get_serial_port_data(port);

	/* Disable flow control */
	if (!on) {
		if (usb_control_msg(port->serial->dev,
			    usb_sndctrlpipe(port->serial->dev, 0),
			    FTDI_SIO_SET_FLOW_CTRL_REQUEST,
			    FTDI_SIO_SET_FLOW_CTRL_REQUEST_TYPE,
			    0, priv->interface, NULL, 0,
			    WDR_TIMEOUT) < 0) {
			dev_err(&port->dev, "error from flowcontrol urb\n");
		}
	}
	/* drop RTS and DTR */
	if (on)
		set_mctrl(port, TIOCM_DTR | TIOCM_RTS);
	else
		clear_mctrl(port, TIOCM_DTR | TIOCM_RTS);
}