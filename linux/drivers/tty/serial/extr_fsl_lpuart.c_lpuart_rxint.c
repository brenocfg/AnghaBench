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
struct tty_port {int dummy; } ;
struct TYPE_5__ {unsigned int overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; } ;
struct TYPE_6__ {unsigned char ignore_status_mask; unsigned char read_status_mask; int /*<<< orphan*/  lock; scalar_t__ membase; TYPE_2__ icount; scalar_t__ sysrq; TYPE_1__* state; } ;
struct lpuart_port {TYPE_3__ port; } ;
struct TYPE_4__ {struct tty_port port; } ;

/* Variables and functions */
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_OVERRUN ; 
 unsigned int TTY_PARITY ; 
 scalar_t__ UARTCFIFO ; 
 int /*<<< orphan*/  UARTCFIFO_RXFLUSH ; 
 scalar_t__ UARTDR ; 
 scalar_t__ UARTSFIFO ; 
 unsigned char UARTSFIFO_RXEMPT ; 
 int /*<<< orphan*/  UARTSFIFO_RXOF ; 
 scalar_t__ UARTSR1 ; 
 unsigned char UARTSR1_FE ; 
 unsigned char UARTSR1_OR ; 
 unsigned char UARTSR1_PE ; 
 unsigned char readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,unsigned char,unsigned int) ; 
 scalar_t__ uart_handle_sysrq_char (TYPE_3__*,unsigned char) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void lpuart_rxint(struct lpuart_port *sport)
{
	unsigned int flg, ignored = 0, overrun = 0;
	struct tty_port *port = &sport->port.state->port;
	unsigned long flags;
	unsigned char rx, sr;

	spin_lock_irqsave(&sport->port.lock, flags);

	while (!(readb(sport->port.membase + UARTSFIFO) & UARTSFIFO_RXEMPT)) {
		flg = TTY_NORMAL;
		sport->port.icount.rx++;
		/*
		 * to clear the FE, OR, NF, FE, PE flags,
		 * read SR1 then read DR
		 */
		sr = readb(sport->port.membase + UARTSR1);
		rx = readb(sport->port.membase + UARTDR);

		if (uart_handle_sysrq_char(&sport->port, (unsigned char)rx))
			continue;

		if (sr & (UARTSR1_PE | UARTSR1_OR | UARTSR1_FE)) {
			if (sr & UARTSR1_PE)
				sport->port.icount.parity++;
			else if (sr & UARTSR1_FE)
				sport->port.icount.frame++;

			if (sr & UARTSR1_OR)
				overrun++;

			if (sr & sport->port.ignore_status_mask) {
				if (++ignored > 100)
					goto out;
				continue;
			}

			sr &= sport->port.read_status_mask;

			if (sr & UARTSR1_PE)
				flg = TTY_PARITY;
			else if (sr & UARTSR1_FE)
				flg = TTY_FRAME;

			if (sr & UARTSR1_OR)
				flg = TTY_OVERRUN;

#ifdef SUPPORT_SYSRQ
			sport->port.sysrq = 0;
#endif
		}

		tty_insert_flip_char(port, rx, flg);
	}

out:
	if (overrun) {
		sport->port.icount.overrun += overrun;

		/*
		 * Overruns cause FIFO pointers to become missaligned.
		 * Flushing the receive FIFO reinitializes the pointers.
		 */
		writeb(UARTCFIFO_RXFLUSH, sport->port.membase + UARTCFIFO);
		writeb(UARTSFIFO_RXOF, sport->port.membase + UARTSFIFO);
	}

	spin_unlock_irqrestore(&sport->port.lock, flags);

	tty_flip_buffer_push(port);
}