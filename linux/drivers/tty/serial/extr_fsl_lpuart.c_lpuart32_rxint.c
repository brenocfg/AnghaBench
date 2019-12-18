#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_port {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; } ;
struct TYPE_7__ {unsigned long ignore_status_mask; unsigned long read_status_mask; int /*<<< orphan*/  lock; scalar_t__ sysrq; TYPE_2__ icount; TYPE_1__* state; } ;
struct lpuart_port {TYPE_3__ port; } ;
struct TYPE_5__ {struct tty_port port; } ;

/* Variables and functions */
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_OVERRUN ; 
 unsigned int TTY_PARITY ; 
 int /*<<< orphan*/  UARTDATA ; 
 int /*<<< orphan*/  UARTFIFO ; 
 unsigned long UARTFIFO_RXEMPT ; 
 int /*<<< orphan*/  UARTSTAT ; 
 unsigned long UARTSTAT_FE ; 
 unsigned long UARTSTAT_OR ; 
 unsigned long UARTSTAT_PE ; 
 unsigned long lpuart32_read (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,unsigned long,unsigned int) ; 
 scalar_t__ uart_handle_sysrq_char (TYPE_3__*,unsigned char) ; 

__attribute__((used)) static void lpuart32_rxint(struct lpuart_port *sport)
{
	unsigned int flg, ignored = 0;
	struct tty_port *port = &sport->port.state->port;
	unsigned long flags;
	unsigned long rx, sr;

	spin_lock_irqsave(&sport->port.lock, flags);

	while (!(lpuart32_read(&sport->port, UARTFIFO) & UARTFIFO_RXEMPT)) {
		flg = TTY_NORMAL;
		sport->port.icount.rx++;
		/*
		 * to clear the FE, OR, NF, FE, PE flags,
		 * read STAT then read DATA reg
		 */
		sr = lpuart32_read(&sport->port, UARTSTAT);
		rx = lpuart32_read(&sport->port, UARTDATA);
		rx &= 0x3ff;

		if (uart_handle_sysrq_char(&sport->port, (unsigned char)rx))
			continue;

		if (sr & (UARTSTAT_PE | UARTSTAT_OR | UARTSTAT_FE)) {
			if (sr & UARTSTAT_PE)
				sport->port.icount.parity++;
			else if (sr & UARTSTAT_FE)
				sport->port.icount.frame++;

			if (sr & UARTSTAT_OR)
				sport->port.icount.overrun++;

			if (sr & sport->port.ignore_status_mask) {
				if (++ignored > 100)
					goto out;
				continue;
			}

			sr &= sport->port.read_status_mask;

			if (sr & UARTSTAT_PE)
				flg = TTY_PARITY;
			else if (sr & UARTSTAT_FE)
				flg = TTY_FRAME;

			if (sr & UARTSTAT_OR)
				flg = TTY_OVERRUN;

#ifdef SUPPORT_SYSRQ
			sport->port.sysrq = 0;
#endif
		}

		tty_insert_flip_char(port, rx, flg);
	}

out:
	spin_unlock_irqrestore(&sport->port.lock, flags);

	tty_flip_buffer_push(port);
}