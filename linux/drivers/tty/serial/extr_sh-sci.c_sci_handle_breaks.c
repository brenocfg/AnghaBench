#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  brk; } ;
struct uart_port {int /*<<< orphan*/  dev; TYPE_2__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCxSR ; 
 unsigned short SCxSR_BRK (struct uart_port*) ; 
 int /*<<< orphan*/  TTY_BREAK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sci_handle_fifo_overrun (struct uart_port*) ; 
 unsigned short serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 scalar_t__ tty_insert_flip_char (struct tty_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 

__attribute__((used)) static int sci_handle_breaks(struct uart_port *port)
{
	int copied = 0;
	unsigned short status = serial_port_in(port, SCxSR);
	struct tty_port *tport = &port->state->port;

	if (uart_handle_break(port))
		return 0;

	if (status & SCxSR_BRK(port)) {
		port->icount.brk++;

		/* Notify of BREAK */
		if (tty_insert_flip_char(tport, 0, TTY_BREAK))
			copied++;

		dev_dbg(port->dev, "BREAK detected\n");
	}

	if (copied)
		tty_flip_buffer_push(tport);

	copied += sci_handle_fifo_overrun(port);

	return copied;
}