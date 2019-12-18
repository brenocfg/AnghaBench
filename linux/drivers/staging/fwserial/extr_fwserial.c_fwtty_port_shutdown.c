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
struct tty_port {int dummy; } ;
struct fwtty_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_fifo; scalar_t__ overrun; scalar_t__ break_ctl; scalar_t__ flags; int /*<<< orphan*/  drain; int /*<<< orphan*/  emit_breaks; } ;

/* Variables and functions */
 int /*<<< orphan*/  __fwtty_write_port_status (struct fwtty_port*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fifo_free (int /*<<< orphan*/ *) ; 
 struct fwtty_port* port ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct fwtty_port* to_port (struct tty_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fwtty_port_shutdown(struct tty_port *tty_port)
{
	struct fwtty_port *port = to_port(tty_port, port);

	/* TODO: cancel outstanding transactions */

	cancel_delayed_work_sync(&port->emit_breaks);
	cancel_delayed_work_sync(&port->drain);

	spin_lock_bh(&port->lock);
	port->flags = 0;
	port->break_ctl = 0;
	port->overrun = 0;
	__fwtty_write_port_status(port);
	dma_fifo_free(&port->tx_fifo);
	spin_unlock_bh(&port->lock);
}