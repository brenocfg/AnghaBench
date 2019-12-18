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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  rx; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_2__* state; TYPE_1__ icount; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDA_UART_RXTX_BUFFER ; 
 int RDA_UART_RX_FIFO_MASK ; 
 int RDA_UART_RX_FRAMING_ERR ; 
 int RDA_UART_RX_OVERFLOW_ERR ; 
 int RDA_UART_RX_PARITY_ERR ; 
 int /*<<< orphan*/  RDA_UART_STATUS ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 char TTY_PARITY ; 
 int rda_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ *,int,char) ; 

__attribute__((used)) static void rda_uart_receive_chars(struct uart_port *port)
{
	u32 status, val;

	status = rda_uart_read(port, RDA_UART_STATUS);
	while ((status & RDA_UART_RX_FIFO_MASK)) {
		char flag = TTY_NORMAL;

		if (status & RDA_UART_RX_PARITY_ERR) {
			port->icount.parity++;
			flag = TTY_PARITY;
		}

		if (status & RDA_UART_RX_FRAMING_ERR) {
			port->icount.frame++;
			flag = TTY_FRAME;
		}

		if (status & RDA_UART_RX_OVERFLOW_ERR) {
			port->icount.overrun++;
			flag = TTY_OVERRUN;
		}

		val = rda_uart_read(port, RDA_UART_RXTX_BUFFER);
		val &= 0xff;

		port->icount.rx++;
		tty_insert_flip_char(&port->state->port, val, flag);

		status = rda_uart_read(port, RDA_UART_STATUS);
	}

	spin_unlock(&port->lock);
	tty_flip_buffer_push(&port->state->port);
	spin_lock(&port->lock);
}