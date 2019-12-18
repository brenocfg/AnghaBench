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
struct tty_struct {struct fwtty_port* driver_data; } ;
struct fwtty_port {unsigned int mctrl; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int MCTRL_MASK ; 
 int /*<<< orphan*/  __fwtty_write_port_status (struct fwtty_port*) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fwtty_tiocmset(struct tty_struct *tty,
			  unsigned int set, unsigned int clear)
{
	struct fwtty_port *port = tty->driver_data;

	fwtty_dbg(port, "set: %x clear: %x\n", set, clear);

	/* TODO: simulate loopback if TIOCM_LOOP set */

	spin_lock_bh(&port->lock);
	port->mctrl &= ~(clear & MCTRL_MASK & 0xffff);
	port->mctrl |= set & MCTRL_MASK & 0xffff;
	__fwtty_write_port_status(port);
	spin_unlock_bh(&port->lock);
	return 0;
}