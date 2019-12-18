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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct uart_8250_port {int ier; TYPE_1__* dma; } ;
struct TYPE_2__ {scalar_t__ tx_err; } ;

/* Variables and functions */
 int UART_IER_THRI ; 
 unsigned int UART_IIR_NO_INT ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned char UART_LSR_BI ; 
 unsigned char UART_LSR_DR ; 
 unsigned char UART_LSR_THRE ; 
 scalar_t__ handle_rx_dma (struct uart_8250_port*,unsigned int) ; 
 int /*<<< orphan*/  serial8250_modem_status (struct uart_8250_port*) ; 
 unsigned char serial8250_rx_chars (struct uart_8250_port*,unsigned char) ; 
 int /*<<< orphan*/  serial8250_tx_chars (struct uart_8250_port*) ; 
 unsigned char serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uart_unlock_and_check_sysrq (struct uart_port*,unsigned long) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

int serial8250_handle_irq(struct uart_port *port, unsigned int iir)
{
	unsigned char status;
	unsigned long flags;
	struct uart_8250_port *up = up_to_u8250p(port);

	if (iir & UART_IIR_NO_INT)
		return 0;

	spin_lock_irqsave(&port->lock, flags);

	status = serial_port_in(port, UART_LSR);

	if (status & (UART_LSR_DR | UART_LSR_BI)) {
		if (!up->dma || handle_rx_dma(up, iir))
			status = serial8250_rx_chars(up, status);
	}
	serial8250_modem_status(up);
	if ((!up->dma || up->dma->tx_err) && (status & UART_LSR_THRE) &&
		(up->ier & UART_IER_THRI))
		serial8250_tx_chars(up);

	uart_unlock_and_check_sysrq(port, flags);
	return 1;
}