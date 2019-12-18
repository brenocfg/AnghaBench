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
struct uart_state {int dummy; } ;
struct uart_port {char x_char; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct tty_struct {struct uart_state* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start_tx ) (struct uart_port*) ;int /*<<< orphan*/  (* send_xchar ) (struct uart_port*,char) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,char) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*) ; 
 int /*<<< orphan*/  uart_port_deref (struct uart_port*) ; 
 struct uart_port* uart_port_ref (struct uart_state*) ; 

__attribute__((used)) static void uart_send_xchar(struct tty_struct *tty, char ch)
{
	struct uart_state *state = tty->driver_data;
	struct uart_port *port;
	unsigned long flags;

	port = uart_port_ref(state);
	if (!port)
		return;

	if (port->ops->send_xchar)
		port->ops->send_xchar(port, ch);
	else {
		spin_lock_irqsave(&port->lock, flags);
		port->x_char = ch;
		if (ch)
			port->ops->start_tx(port);
		spin_unlock_irqrestore(&port->lock, flags);
	}
	uart_port_deref(port);
}