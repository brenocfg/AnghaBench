#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_port {unsigned int (* serial_in ) (struct uart_port*,int /*<<< orphan*/ ) ;TYPE_1__* ops; } ;
struct TYPE_5__ {unsigned char (* serial_in ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; } ;
struct uart_8250_port {unsigned char lsr_saved_flags; int ier; scalar_t__ overrun_backoff_time_ms; TYPE_2__ port; int /*<<< orphan*/  overrun_backoff; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop_rx ) (struct uart_port*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int /*<<< orphan*/  UART_IIR ; 
 unsigned int UART_IIR_NO_INT ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned char UART_LSR_BI ; 
 unsigned char UART_LSR_DR ; 
 unsigned char UART_LSR_OE ; 
 unsigned char UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_RX ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  serial8250_modem_status (struct uart_8250_port*) ; 
 unsigned char serial8250_rx_chars (struct uart_8250_port*,unsigned char) ; 
 int /*<<< orphan*/  serial8250_tx_chars (struct uart_8250_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int stub1 (struct uart_port*,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (struct uart_port*,int /*<<< orphan*/ ) ; 
 unsigned char stub3 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 unsigned int stub4 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct uart_port*) ; 
 int /*<<< orphan*/  uart_unlock_and_check_sysrq (TYPE_2__*,unsigned long) ; 
 scalar_t__ unlikely (unsigned char) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

int fsl8250_handle_irq(struct uart_port *port)
{
	unsigned char lsr, orig_lsr;
	unsigned long flags;
	unsigned int iir;
	struct uart_8250_port *up = up_to_u8250p(port);

	spin_lock_irqsave(&up->port.lock, flags);

	iir = port->serial_in(port, UART_IIR);
	if (iir & UART_IIR_NO_INT) {
		spin_unlock_irqrestore(&up->port.lock, flags);
		return 0;
	}

	/* This is the WAR; if last event was BRK, then read and return */
	if (unlikely(up->lsr_saved_flags & UART_LSR_BI)) {
		up->lsr_saved_flags &= ~UART_LSR_BI;
		port->serial_in(port, UART_RX);
		spin_unlock_irqrestore(&up->port.lock, flags);
		return 1;
	}

	lsr = orig_lsr = up->port.serial_in(&up->port, UART_LSR);

	/* Process incoming characters first */
	if ((lsr & (UART_LSR_DR | UART_LSR_BI)) &&
	    (up->ier & (UART_IER_RLSI | UART_IER_RDI))) {
		lsr = serial8250_rx_chars(up, lsr);
	}

	/* Stop processing interrupts on input overrun */
	if ((orig_lsr & UART_LSR_OE) && (up->overrun_backoff_time_ms > 0)) {
		unsigned long delay;

		up->ier = port->serial_in(port, UART_IER);
		if (up->ier & (UART_IER_RLSI | UART_IER_RDI)) {
			port->ops->stop_rx(port);
		} else {
			/* Keep restarting the timer until
			 * the input overrun subsides.
			 */
			cancel_delayed_work(&up->overrun_backoff);
		}

		delay = msecs_to_jiffies(up->overrun_backoff_time_ms);
		schedule_delayed_work(&up->overrun_backoff, delay);
	}

	serial8250_modem_status(up);

	if (lsr & UART_LSR_THRE)
		serial8250_tx_chars(up);

	up->lsr_saved_flags = orig_lsr;
	uart_unlock_and_check_sysrq(&up->port, flags);
	return 1;
}