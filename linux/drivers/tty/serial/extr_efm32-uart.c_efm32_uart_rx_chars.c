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
struct TYPE_3__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct uart_port {int read_status_mask; int ignore_status_mask; TYPE_2__* state; TYPE_1__ icount; } ;
struct efm32_uart_port {struct uart_port port; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int SW_UARTn_RXDATAX_BERR ; 
 int TTY_BREAK ; 
 int TTY_FRAME ; 
 int TTY_PARITY ; 
 int /*<<< orphan*/  UARTn_RXDATAX ; 
 int UARTn_RXDATAX_FERR ; 
 int UARTn_RXDATAX_PERR ; 
 int UARTn_RXDATAX_RXDATA__MASK ; 
 int /*<<< orphan*/  UARTn_STATUS ; 
 int UARTn_STATUS_RXDATAV ; 
 int efm32_uart_read32 (struct efm32_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_insert_flip_char (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,int) ; 

__attribute__((used)) static void efm32_uart_rx_chars(struct efm32_uart_port *efm_port)
{
	struct uart_port *port = &efm_port->port;

	while (efm32_uart_read32(efm_port, UARTn_STATUS) &
			UARTn_STATUS_RXDATAV) {
		u32 rxdata = efm32_uart_read32(efm_port, UARTn_RXDATAX);
		int flag = 0;

		/*
		 * This is a reserved bit and I only saw it read as 0. But to be
		 * sure not to be confused too much by new devices adhere to the
		 * warning in the reference manual that reserverd bits might
		 * read as 1 in the future.
		 */
		rxdata &= ~SW_UARTn_RXDATAX_BERR;

		port->icount.rx++;

		if ((rxdata & UARTn_RXDATAX_FERR) &&
				!(rxdata & UARTn_RXDATAX_RXDATA__MASK)) {
			rxdata |= SW_UARTn_RXDATAX_BERR;
			port->icount.brk++;
			if (uart_handle_break(port))
				continue;
		} else if (rxdata & UARTn_RXDATAX_PERR)
			port->icount.parity++;
		else if (rxdata & UARTn_RXDATAX_FERR)
			port->icount.frame++;

		rxdata &= port->read_status_mask;

		if (rxdata & SW_UARTn_RXDATAX_BERR)
			flag = TTY_BREAK;
		else if (rxdata & UARTn_RXDATAX_PERR)
			flag = TTY_PARITY;
		else if (rxdata & UARTn_RXDATAX_FERR)
			flag = TTY_FRAME;
		else if (uart_handle_sysrq_char(port,
					rxdata & UARTn_RXDATAX_RXDATA__MASK))
			continue;

		if ((rxdata & port->ignore_status_mask) == 0)
			tty_insert_flip_char(&port->state->port,
					rxdata & UARTn_RXDATAX_RXDATA__MASK, flag);
	}
}