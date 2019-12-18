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
struct fwtty_port {int break_ctl; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_fifo; int /*<<< orphan*/  wait_tx; } ;

/* Variables and functions */
 int EINTR ; 
 long ERESTARTSYS ; 
 int /*<<< orphan*/  IN_TX ; 
 int /*<<< orphan*/  STOP_TX ; 
 int /*<<< orphan*/  __fwtty_write_port_status (struct fwtty_port*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fifo_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwtty_dbg (struct fwtty_port*,char*,int) ; 
 int /*<<< orphan*/  fwtty_restart_tx (struct fwtty_port*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int fwtty_break_ctl(struct tty_struct *tty, int state)
{
	struct fwtty_port *port = tty->driver_data;
	long ret;

	fwtty_dbg(port, "%d\n", state);

	if (state == -1) {
		set_bit(STOP_TX, &port->flags);
		ret = wait_event_interruptible_timeout(port->wait_tx,
					       !test_bit(IN_TX, &port->flags),
					       10);
		if (ret == 0 || ret == -ERESTARTSYS) {
			clear_bit(STOP_TX, &port->flags);
			fwtty_restart_tx(port);
			return -EINTR;
		}
	}

	spin_lock_bh(&port->lock);
	port->break_ctl = (state == -1);
	__fwtty_write_port_status(port);
	spin_unlock_bh(&port->lock);

	if (state == 0) {
		spin_lock_bh(&port->lock);
		dma_fifo_reset(&port->tx_fifo);
		clear_bit(STOP_TX, &port->flags);
		spin_unlock_bh(&port->lock);
	}
	return 0;
}