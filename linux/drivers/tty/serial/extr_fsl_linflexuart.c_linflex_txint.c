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
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; scalar_t__ x_char; TYPE_1__* state; } ;
struct circ_buf {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct circ_buf xmit; } ;

/* Variables and functions */
 scalar_t__ BDRL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long LINFLEXD_UARTSR_DTFTFF ; 
 scalar_t__ UARTSR ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  linflex_stop_tx (struct uart_port*) ; 
 int /*<<< orphan*/  linflex_transmit_buffer (struct uart_port*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (struct uart_port*) ; 
 int /*<<< orphan*/  uart_write_wakeup (struct uart_port*) ; 
 int /*<<< orphan*/  writeb (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static irqreturn_t linflex_txint(int irq, void *dev_id)
{
	struct uart_port *sport = dev_id;
	struct circ_buf *xmit = &sport->state->xmit;
	unsigned long flags;
	unsigned long status;

	spin_lock_irqsave(&sport->lock, flags);

	if (sport->x_char) {
		writeb(sport->x_char, sport->membase + BDRL);

		/* waiting for data transmission completed */
		while (((status = readl(sport->membase + UARTSR)) &
			LINFLEXD_UARTSR_DTFTFF) != LINFLEXD_UARTSR_DTFTFF)
			;

		writel(status | LINFLEXD_UARTSR_DTFTFF,
		       sport->membase + UARTSR);

		goto out;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(sport)) {
		linflex_stop_tx(sport);
		goto out;
	}

	linflex_transmit_buffer(sport);

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(sport);

out:
	spin_unlock_irqrestore(&sport->lock, flags);
	return IRQ_HANDLED;
}