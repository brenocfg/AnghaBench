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
struct TYPE_4__ {int /*<<< orphan*/  rx; } ;
struct uart_port {int /*<<< orphan*/  lock; scalar_t__ membase; TYPE_2__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 scalar_t__ BDRM ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long LINFLEXD_UARTSR_BOF ; 
 unsigned long LINFLEXD_UARTSR_DRFRFE ; 
 unsigned long LINFLEXD_UARTSR_FEF ; 
 unsigned long LINFLEXD_UARTSR_PE ; 
 unsigned long LINFLEXD_UARTSR_RMB ; 
 unsigned long LINFLEXD_UARTSR_SZF ; 
 unsigned int TTY_NORMAL ; 
 scalar_t__ UARTSR ; 
 unsigned char readb (scalar_t__) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  uart_handle_break (struct uart_port*) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned char) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static irqreturn_t linflex_rxint(int irq, void *dev_id)
{
	struct uart_port *sport = dev_id;
	unsigned int flg;
	struct tty_port *port = &sport->state->port;
	unsigned long flags, status;
	unsigned char rx;
	bool brk;

	spin_lock_irqsave(&sport->lock, flags);

	status = readl(sport->membase + UARTSR);
	while (status & LINFLEXD_UARTSR_RMB) {
		rx = readb(sport->membase + BDRM);
		brk = false;
		flg = TTY_NORMAL;
		sport->icount.rx++;

		if (status & (LINFLEXD_UARTSR_BOF | LINFLEXD_UARTSR_SZF |
			      LINFLEXD_UARTSR_FEF | LINFLEXD_UARTSR_PE)) {
			if (status & LINFLEXD_UARTSR_SZF)
				status |= LINFLEXD_UARTSR_SZF;
			if (status & LINFLEXD_UARTSR_BOF)
				status |= LINFLEXD_UARTSR_BOF;
			if (status & LINFLEXD_UARTSR_FEF) {
				if (!rx)
					brk = true;
				status |= LINFLEXD_UARTSR_FEF;
			}
			if (status & LINFLEXD_UARTSR_PE)
				status |=  LINFLEXD_UARTSR_PE;
		}

		writel(status | LINFLEXD_UARTSR_RMB | LINFLEXD_UARTSR_DRFRFE,
		       sport->membase + UARTSR);
		status = readl(sport->membase + UARTSR);

		if (brk) {
			uart_handle_break(sport);
		} else {
#ifdef SUPPORT_SYSRQ
			if (uart_handle_sysrq_char(sport, (unsigned char)rx))
				continue;
#endif
			tty_insert_flip_char(port, rx, flg);
		}
	}

	spin_unlock_irqrestore(&sport->lock, flags);

	tty_flip_buffer_push(port);

	return IRQ_HANDLED;
}