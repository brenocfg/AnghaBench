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
struct TYPE_2__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct async_icount {int dummy; } ;
struct usb_serial_port {TYPE_1__ port; int /*<<< orphan*/  lock; struct async_icount icount; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_initialized (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_serial_generic_msr_changed (struct tty_struct*,unsigned long,struct async_icount*) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int usb_serial_generic_tiocmiwait(struct tty_struct *tty, unsigned long arg)
{
	struct usb_serial_port *port = tty->driver_data;
	struct async_icount cnow;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&port->lock, flags);
	cnow = port->icount;				/* atomic copy */
	spin_unlock_irqrestore(&port->lock, flags);

	ret = wait_event_interruptible(port->port.delta_msr_wait,
			usb_serial_generic_msr_changed(tty, arg, &cnow));
	if (!ret && !tty_port_initialized(&port->port))
		ret = -EIO;

	return ret;
}