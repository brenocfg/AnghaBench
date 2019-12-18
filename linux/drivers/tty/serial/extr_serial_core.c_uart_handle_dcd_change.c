#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dcd; } ;
struct uart_port {TYPE_2__ icount; int /*<<< orphan*/  lock; TYPE_3__* state; } ;
struct tty_struct {int dummy; } ;
struct tty_port {int /*<<< orphan*/  open_wait; struct tty_struct* tty; } ;
struct tty_ldisc {TYPE_1__* ops; } ;
struct TYPE_6__ {struct tty_port port; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dcd_change ) (struct tty_struct*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,unsigned int) ; 
 int /*<<< orphan*/  tty_hangup (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_deref (struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_ref (struct tty_struct*) ; 
 scalar_t__ uart_dcd_enabled (struct uart_port*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void uart_handle_dcd_change(struct uart_port *uport, unsigned int status)
{
	struct tty_port *port = &uport->state->port;
	struct tty_struct *tty = port->tty;
	struct tty_ldisc *ld;

	lockdep_assert_held_once(&uport->lock);

	if (tty) {
		ld = tty_ldisc_ref(tty);
		if (ld) {
			if (ld->ops->dcd_change)
				ld->ops->dcd_change(tty, status);
			tty_ldisc_deref(ld);
		}
	}

	uport->icount.dcd++;

	if (uart_dcd_enabled(uport)) {
		if (status)
			wake_up_interruptible(&port->open_wait);
		else if (tty)
			tty_hangup(tty);
	}
}