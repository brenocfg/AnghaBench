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
struct tty_struct {struct fwtty_port* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  unthrottle; } ;
struct fwtty_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 int /*<<< orphan*/  OOB_RX_THROTTLE ; 
 int /*<<< orphan*/  TIOCM_RTS ; 
 int /*<<< orphan*/  __fwtty_write_port_status (struct fwtty_port*) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,int) ; 
 int /*<<< orphan*/  fwtty_profile_fifo (struct fwtty_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fwtty_unthrottle(struct tty_struct *tty)
{
	struct fwtty_port *port = tty->driver_data;

	fwtty_dbg(port, "CRTSCTS: %d\n", C_CRTSCTS(tty) != 0);

	fwtty_profile_fifo(port, port->stats.unthrottle);

	spin_lock_bh(&port->lock);
	port->mctrl &= ~OOB_RX_THROTTLE;
	if (C_CRTSCTS(tty))
		port->mctrl |= TIOCM_RTS;
	__fwtty_write_port_status(port);
	spin_unlock_bh(&port->lock);
}