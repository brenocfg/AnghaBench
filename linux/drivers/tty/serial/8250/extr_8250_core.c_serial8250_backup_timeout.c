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
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ irq; scalar_t__ x_char; TYPE_1__* state; } ;
struct uart_8250_port {unsigned int lsr_saved_flags; int ier; TYPE_2__ port; int /*<<< orphan*/  timer; } ;
struct timer_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  xmit; } ;

/* Variables and functions */
 int HZ ; 
 unsigned int LSR_SAVE_FLAGS ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_THRI ; 
 int /*<<< orphan*/  UART_IIR ; 
 unsigned int UART_IIR_ID ; 
 unsigned int UART_IIR_NO_INT ; 
 unsigned int UART_IIR_THRI ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned int UART_LSR_THRE ; 
 struct uart_8250_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  serial8250_tx_chars (struct uart_8250_port*) ; 
 unsigned int serial_in (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  uart_circ_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_poll_timeout (TYPE_2__*) ; 
 struct uart_8250_port* up ; 

__attribute__((used)) static void serial8250_backup_timeout(struct timer_list *t)
{
	struct uart_8250_port *up = from_timer(up, t, timer);
	unsigned int iir, ier = 0, lsr;
	unsigned long flags;

	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Must disable interrupts or else we risk racing with the interrupt
	 * based handler.
	 */
	if (up->port.irq) {
		ier = serial_in(up, UART_IER);
		serial_out(up, UART_IER, 0);
	}

	iir = serial_in(up, UART_IIR);

	/*
	 * This should be a safe test for anyone who doesn't trust the
	 * IIR bits on their UART, but it's specifically designed for
	 * the "Diva" UART used on the management processor on many HP
	 * ia64 and parisc boxes.
	 */
	lsr = serial_in(up, UART_LSR);
	up->lsr_saved_flags |= lsr & LSR_SAVE_FLAGS;
	if ((iir & UART_IIR_NO_INT) && (up->ier & UART_IER_THRI) &&
	    (!uart_circ_empty(&up->port.state->xmit) || up->port.x_char) &&
	    (lsr & UART_LSR_THRE)) {
		iir &= ~(UART_IIR_ID | UART_IIR_NO_INT);
		iir |= UART_IIR_THRI;
	}

	if (!(iir & UART_IIR_NO_INT))
		serial8250_tx_chars(up);

	if (up->port.irq)
		serial_out(up, UART_IER, ier);

	spin_unlock_irqrestore(&up->port.lock, flags);

	/* Standard timer interval plus 0.2s to keep the port running */
	mod_timer(&up->timer,
		jiffies + uart_poll_timeout(&up->port) + HZ / 5);
}