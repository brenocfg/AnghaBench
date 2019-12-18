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
struct sdio_uart_port {int /*<<< orphan*/ * in_sdio_uart_irq; } ;
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IIR ; 
 unsigned int UART_IIR_NO_INT ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned int UART_LSR_DR ; 
 unsigned int UART_LSR_THRE ; 
 int /*<<< orphan*/ * current ; 
 struct sdio_uart_port* sdio_get_drvdata (struct sdio_func*) ; 
 unsigned int sdio_in (struct sdio_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_uart_check_modem_status (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  sdio_uart_receive_chars (struct sdio_uart_port*,unsigned int*) ; 
 int /*<<< orphan*/  sdio_uart_transmit_chars (struct sdio_uart_port*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sdio_uart_irq(struct sdio_func *func)
{
	struct sdio_uart_port *port = sdio_get_drvdata(func);
	unsigned int iir, lsr;

	/*
	 * In a few places sdio_uart_irq() is called directly instead of
	 * waiting for the actual interrupt to be raised and the SDIO IRQ
	 * thread scheduled in order to reduce latency.  However, some
	 * interaction with the tty core may end up calling us back
	 * (serial echo, flow control, etc.) through those same places
	 * causing undesirable effects.  Let's stop the recursion here.
	 */
	if (unlikely(port->in_sdio_uart_irq == current))
		return;

	iir = sdio_in(port, UART_IIR);
	if (iir & UART_IIR_NO_INT)
		return;

	port->in_sdio_uart_irq = current;
	lsr = sdio_in(port, UART_LSR);
	if (lsr & UART_LSR_DR)
		sdio_uart_receive_chars(port, &lsr);
	sdio_uart_check_modem_status(port);
	if (lsr & UART_LSR_THRE)
		sdio_uart_transmit_chars(port);
	port->in_sdio_uart_irq = NULL;
}