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
struct TYPE_4__ {int /*<<< orphan*/  buf_overrun; } ;
struct uart_port {unsigned int ignore_status_mask; TYPE_2__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 unsigned int TTY_OVERRUN ; 
 scalar_t__ tty_insert_flip_char (struct tty_port*,unsigned int,unsigned int) ; 

void uart_insert_char(struct uart_port *port, unsigned int status,
		 unsigned int overrun, unsigned int ch, unsigned int flag)
{
	struct tty_port *tport = &port->state->port;

	if ((status & port->ignore_status_mask & ~overrun) == 0)
		if (tty_insert_flip_char(tport, ch, flag) == 0)
			++port->icount.buf_overrun;

	/*
	 * Overrun is special.  Since it's reported immediately,
	 * it doesn't affect the current character.
	 */
	if (status & ~port->ignore_status_mask & overrun)
		if (tty_insert_flip_char(tport, 0, TTY_OVERRUN) == 0)
			++port->icount.buf_overrun;
}