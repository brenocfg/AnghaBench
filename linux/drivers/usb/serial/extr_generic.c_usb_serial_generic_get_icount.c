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
struct async_icount {int /*<<< orphan*/  buf_overrun; int /*<<< orphan*/  brk; int /*<<< orphan*/  overrun; int /*<<< orphan*/  parity; int /*<<< orphan*/  frame; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct usb_serial_port {int /*<<< orphan*/  lock; struct async_icount icount; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct serial_icounter_struct {int /*<<< orphan*/  buf_overrun; int /*<<< orphan*/  brk; int /*<<< orphan*/  overrun; int /*<<< orphan*/  parity; int /*<<< orphan*/  frame; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int usb_serial_generic_get_icount(struct tty_struct *tty,
					struct serial_icounter_struct *icount)
{
	struct usb_serial_port *port = tty->driver_data;
	struct async_icount cnow;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	cnow = port->icount;				/* atomic copy */
	spin_unlock_irqrestore(&port->lock, flags);

	icount->cts = cnow.cts;
	icount->dsr = cnow.dsr;
	icount->rng = cnow.rng;
	icount->dcd = cnow.dcd;
	icount->tx = cnow.tx;
	icount->rx = cnow.rx;
	icount->frame = cnow.frame;
	icount->parity = cnow.parity;
	icount->overrun = cnow.overrun;
	icount->brk = cnow.brk;
	icount->buf_overrun = cnow.buf_overrun;

	return 0;
}