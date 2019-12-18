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
typedef  int upstat_t ;
struct uart_state {int dummy; } ;
struct uart_port {int status; TYPE_1__* ops; } ;
struct tty_struct {struct uart_state* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* throttle ) (struct uart_port*) ;} ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 scalar_t__ I_IXOFF (struct tty_struct*) ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  TIOCM_RTS ; 
 int UPSTAT_AUTORTS ; 
 int UPSTAT_AUTOXOFF ; 
 int UPSTAT_SYNC_FIFO ; 
 int /*<<< orphan*/  stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  uart_clear_mctrl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_port_deref (struct uart_port*) ; 
 struct uart_port* uart_port_ref (struct uart_state*) ; 
 int /*<<< orphan*/  uart_send_xchar (struct tty_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uart_throttle(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	upstat_t mask = UPSTAT_SYNC_FIFO;
	struct uart_port *port;

	port = uart_port_ref(state);
	if (!port)
		return;

	if (I_IXOFF(tty))
		mask |= UPSTAT_AUTOXOFF;
	if (C_CRTSCTS(tty))
		mask |= UPSTAT_AUTORTS;

	if (port->status & mask) {
		port->ops->throttle(port);
		mask &= ~port->status;
	}

	if (mask & UPSTAT_AUTORTS)
		uart_clear_mctrl(port, TIOCM_RTS);

	if (mask & UPSTAT_AUTOXOFF)
		uart_send_xchar(tty, STOP_CHAR(tty));

	uart_port_deref(port);
}