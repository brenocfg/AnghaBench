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
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial_port {int dummy; } ;
struct f81534_port_private {int /*<<< orphan*/  msr_lock; int /*<<< orphan*/  shadow_msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  F81534_MODEM_STATUS_REG ; 
 int f81534_get_port_register (struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct f81534_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int f81534_read_msr(struct usb_serial_port *port)
{
	struct f81534_port_private *port_priv = usb_get_serial_port_data(port);
	unsigned long flags;
	int status;
	u8 msr;

	/* Get MSR initial value */
	status = f81534_get_port_register(port, F81534_MODEM_STATUS_REG, &msr);
	if (status)
		return status;

	/* Force update current state */
	spin_lock_irqsave(&port_priv->msr_lock, flags);
	port_priv->shadow_msr = msr;
	spin_unlock_irqrestore(&port_priv->msr_lock, flags);

	return 0;
}