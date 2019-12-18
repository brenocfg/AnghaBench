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
struct TYPE_6__ {unsigned int rx; } ;
struct uart_port {TYPE_3__ icount; TYPE_2__* state; } ;
struct tty_struct {int dummy; } ;
struct sirfsoc_uart_port {TYPE_1__* uart_reg; } ;
struct sirfsoc_register {int /*<<< orphan*/  sirfsoc_rx_fifo_data; int /*<<< orphan*/  sirfsoc_rx_fifo_status; } ;
struct sirfsoc_fifo_status {unsigned int (* ff_empty ) (struct uart_port*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {struct sirfsoc_fifo_status fifo_status; struct sirfsoc_register uart_reg; } ;

/* Variables and functions */
 unsigned int ENODEV ; 
 unsigned int SIRFUART_DUMMY_READ ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 unsigned int rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 unsigned int stub1 (struct uart_port*) ; 
 struct sirfsoc_uart_port* to_sirfport (struct uart_port*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
sirfsoc_uart_pio_rx_chars(struct uart_port *port, unsigned int max_rx_count)
{
	struct sirfsoc_uart_port *sirfport = to_sirfport(port);
	struct sirfsoc_register *ureg = &sirfport->uart_reg->uart_reg;
	struct sirfsoc_fifo_status *ufifo_st = &sirfport->uart_reg->fifo_status;
	unsigned int ch, rx_count = 0;
	struct tty_struct *tty;
	tty = tty_port_tty_get(&port->state->port);
	if (!tty)
		return -ENODEV;
	while (!(rd_regl(port, ureg->sirfsoc_rx_fifo_status) &
					ufifo_st->ff_empty(port))) {
		ch = rd_regl(port, ureg->sirfsoc_rx_fifo_data) |
			SIRFUART_DUMMY_READ;
		if (unlikely(uart_handle_sysrq_char(port, ch)))
			continue;
		uart_insert_char(port, 0, 0, ch, TTY_NORMAL);
		rx_count++;
		if (rx_count >= max_rx_count)
			break;
	}

	port->icount.rx += rx_count;

	return rx_count;
}