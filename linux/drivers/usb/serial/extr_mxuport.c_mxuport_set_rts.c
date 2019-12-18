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
typedef  int u8 ;
struct usb_serial_port {int /*<<< orphan*/  port_number; struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct mxuport_port {int mcr_state; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MX_RTS_DISABLE 130 
#define  MX_RTS_ENABLE 129 
#define  MX_RTS_HW 128 
 int /*<<< orphan*/  RQ_VENDOR_SET_RTS ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mxuport_send_ctrl_urb (struct usb_serial*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mxuport_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int mxuport_set_rts(struct usb_serial_port *port, u8 state)
{
	struct mxuport_port *mxport = usb_get_serial_port_data(port);
	struct usb_serial *serial = port->serial;
	int err;
	u8 mcr_state;

	mutex_lock(&mxport->mutex);
	mcr_state = mxport->mcr_state;

	switch (state) {
	case MX_RTS_DISABLE:
		mcr_state &= ~UART_MCR_RTS;
		break;
	case MX_RTS_ENABLE:
		mcr_state |= UART_MCR_RTS;
		break;
	case MX_RTS_HW:
		/*
		 * Do not update mxport->mcr_state when doing hardware
		 * flow control.
		 */
		break;
	default:
		/*
		 * Should not happen, but somebody might try passing
		 * MX_RTS_NO_CHANGE, which is not valid.
		 */
		err = -EINVAL;
		goto out;
	}
	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_RTS,
				    state, port->port_number);
	if (!err)
		mxport->mcr_state = mcr_state;

out:
	mutex_unlock(&mxport->mutex);

	return err;
}