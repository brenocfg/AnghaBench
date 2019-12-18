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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct uart_8250_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IIR ; 
 unsigned int UART_IIR_ID ; 
 unsigned int UART_IIR_THRI ; 
 int serial8250_handle_irq (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  serial8250_tx_chars (struct uart_8250_port*) ; 
 unsigned int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

__attribute__((used)) static int serial8250_tx_threshold_handle_irq(struct uart_port *port)
{
	unsigned long flags;
	unsigned int iir = serial_port_in(port, UART_IIR);

	/* TX Threshold IRQ triggered so load up FIFO */
	if ((iir & UART_IIR_ID) == UART_IIR_THRI) {
		struct uart_8250_port *up = up_to_u8250p(port);

		spin_lock_irqsave(&port->lock, flags);
		serial8250_tx_chars(up);
		spin_unlock_irqrestore(&port->lock, flags);
	}

	iir = serial_port_in(port, UART_IIR);
	return serial8250_handle_irq(port, iir);
}