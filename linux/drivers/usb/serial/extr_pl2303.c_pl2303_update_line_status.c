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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_3__ {int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct usb_serial_port {TYPE_2__ port; TYPE_1__ icount; struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct tty_struct {int dummy; } ;
struct pl2303_serial_private {int quirks; } ;
struct pl2303_private {int line_status; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int PL2303_QUIRK_UART_STATE_IDX0 ; 
 int UART_BREAK_ERROR ; 
 int UART_CTS ; 
 int UART_DCD ; 
 int UART_DSR ; 
 int UART_RING ; 
 unsigned int UART_STATE_INDEX ; 
 int UART_STATE_MSR_MASK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_2__*) ; 
 struct pl2303_serial_private* usb_get_serial_data (struct usb_serial*) ; 
 struct pl2303_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_serial_handle_break (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_serial_handle_dcd_change (struct usb_serial_port*,struct tty_struct*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pl2303_update_line_status(struct usb_serial_port *port,
				      unsigned char *data,
				      unsigned int actual_length)
{
	struct usb_serial *serial = port->serial;
	struct pl2303_serial_private *spriv = usb_get_serial_data(serial);
	struct pl2303_private *priv = usb_get_serial_port_data(port);
	struct tty_struct *tty;
	unsigned long flags;
	unsigned int status_idx = UART_STATE_INDEX;
	u8 status;
	u8 delta;

	if (spriv->quirks & PL2303_QUIRK_UART_STATE_IDX0)
		status_idx = 0;

	if (actual_length < status_idx + 1)
		return;

	status = data[status_idx];

	/* Save off the uart status for others to look at */
	spin_lock_irqsave(&priv->lock, flags);
	delta = priv->line_status ^ status;
	priv->line_status = status;
	spin_unlock_irqrestore(&priv->lock, flags);

	if (status & UART_BREAK_ERROR)
		usb_serial_handle_break(port);

	if (delta & UART_STATE_MSR_MASK) {
		if (delta & UART_CTS)
			port->icount.cts++;
		if (delta & UART_DSR)
			port->icount.dsr++;
		if (delta & UART_RING)
			port->icount.rng++;
		if (delta & UART_DCD) {
			port->icount.dcd++;
			tty = tty_port_tty_get(&port->port);
			if (tty) {
				usb_serial_handle_dcd_change(port, tty,
							status & UART_DCD);
				tty_kref_put(tty);
			}
		}

		wake_up_interruptible(&port->port.delta_msr_wait);
	}
}