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
struct TYPE_3__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct uart_port {unsigned int read_status_mask; int /*<<< orphan*/  lock; TYPE_2__* state; TYPE_1__ icount; } ;
struct circ_buf {size_t head; size_t tail; scalar_t__ buf; } ;
struct atmel_uart_port {struct circ_buf rx_ring; } ;
struct atmel_uart_char {unsigned int status; int /*<<< orphan*/  ch; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ATMEL_SERIAL_RINGSIZE ; 
 unsigned int ATMEL_US_FRAME ; 
 unsigned int ATMEL_US_OVRE ; 
 unsigned int ATMEL_US_PARE ; 
 unsigned int ATMEL_US_RXBRK ; 
 unsigned int TTY_BREAK ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_PARITY ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct atmel_uart_port* to_atmel_uart_port (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void atmel_rx_from_ring(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);
	struct circ_buf *ring = &atmel_port->rx_ring;
	unsigned int flg;
	unsigned int status;

	while (ring->head != ring->tail) {
		struct atmel_uart_char c;

		/* Make sure c is loaded after head. */
		smp_rmb();

		c = ((struct atmel_uart_char *)ring->buf)[ring->tail];

		ring->tail = (ring->tail + 1) & (ATMEL_SERIAL_RINGSIZE - 1);

		port->icount.rx++;
		status = c.status;
		flg = TTY_NORMAL;

		/*
		 * note that the error handling code is
		 * out of the main execution path
		 */
		if (unlikely(status & (ATMEL_US_PARE | ATMEL_US_FRAME
				       | ATMEL_US_OVRE | ATMEL_US_RXBRK))) {
			if (status & ATMEL_US_RXBRK) {
				/* ignore side-effect */
				status &= ~(ATMEL_US_PARE | ATMEL_US_FRAME);

				port->icount.brk++;
				if (uart_handle_break(port))
					continue;
			}
			if (status & ATMEL_US_PARE)
				port->icount.parity++;
			if (status & ATMEL_US_FRAME)
				port->icount.frame++;
			if (status & ATMEL_US_OVRE)
				port->icount.overrun++;

			status &= port->read_status_mask;

			if (status & ATMEL_US_RXBRK)
				flg = TTY_BREAK;
			else if (status & ATMEL_US_PARE)
				flg = TTY_PARITY;
			else if (status & ATMEL_US_FRAME)
				flg = TTY_FRAME;
		}


		if (uart_handle_sysrq_char(port, c.ch))
			continue;

		uart_insert_char(port, status, ATMEL_US_OVRE, c.ch, flg);
	}

	/*
	 * Drop the lock here since it might end up calling
	 * uart_start(), which takes the lock.
	 */
	spin_unlock(&port->lock);
	tty_flip_buffer_push(&port->state->port);
	spin_lock(&port->lock);
}