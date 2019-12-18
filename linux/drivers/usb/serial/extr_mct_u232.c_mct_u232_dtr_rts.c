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
struct mct_u232_private {int control_state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  mct_u232_set_modem_ctrl (struct usb_serial_port*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct mct_u232_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void mct_u232_dtr_rts(struct usb_serial_port *port, int on)
{
	unsigned int control_state;
	struct mct_u232_private *priv = usb_get_serial_port_data(port);

	spin_lock_irq(&priv->lock);
	if (on)
		priv->control_state |= TIOCM_DTR | TIOCM_RTS;
	else
		priv->control_state &= ~(TIOCM_DTR | TIOCM_RTS);
	control_state = priv->control_state;
	spin_unlock_irq(&priv->lock);

	mct_u232_set_modem_ctrl(port, control_state);
}