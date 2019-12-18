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
struct uart_state {int /*<<< orphan*/  port; int /*<<< orphan*/  xmit; } ;
struct uart_port {TYPE_1__* ops; } ;
struct tty_struct {int /*<<< orphan*/  index; struct uart_state* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_buffer ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  tty_port_tty_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_circ_clear (int /*<<< orphan*/ *) ; 
 struct uart_port* uart_port_lock (struct uart_state*,unsigned long) ; 
 int /*<<< orphan*/  uart_port_unlock (struct uart_port*,unsigned long) ; 

__attribute__((used)) static void uart_flush_buffer(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	struct uart_port *port;
	unsigned long flags;

	/*
	 * This means you called this function _after_ the port was
	 * closed.  No cookie for you.
	 */
	if (!state) {
		WARN_ON(1);
		return;
	}

	pr_debug("uart_flush_buffer(%d) called\n", tty->index);

	port = uart_port_lock(state, flags);
	if (!port)
		return;
	uart_circ_clear(&state->xmit);
	if (port->ops->flush_buffer)
		port->ops->flush_buffer(port);
	uart_port_unlock(port, flags);
	tty_port_tty_wakeup(&state->port);
}