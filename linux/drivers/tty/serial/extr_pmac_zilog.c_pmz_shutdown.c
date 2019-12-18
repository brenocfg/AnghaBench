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
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;
struct uart_pmac_port {int /*<<< orphan*/  flags; TYPE_1__ port; int /*<<< orphan*/ * curregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMACZILOG_FLAG_IS_OPEN ; 
 size_t R3 ; 
 size_t R5 ; 
 int /*<<< orphan*/  RxENABLE ; 
 int /*<<< orphan*/  SND_BRK ; 
 int /*<<< orphan*/  TxENABLE ; 
 int /*<<< orphan*/  ZS_IS_CONS (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_debug (char*) ; 
 int /*<<< orphan*/  pmz_interrupt_control (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmz_maybe_update_regs (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_set_scc_power (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 

__attribute__((used)) static void pmz_shutdown(struct uart_port *port)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned long flags;

	pmz_debug("pmz: shutdown()\n");

	spin_lock_irqsave(&port->lock, flags);

	/* Disable interrupt requests for the channel */
	pmz_interrupt_control(uap, 0);

	if (!ZS_IS_CONS(uap)) {
		/* Disable receiver and transmitter */
		uap->curregs[R3] &= ~RxENABLE;
		uap->curregs[R5] &= ~TxENABLE;

		/* Disable break assertion */
		uap->curregs[R5] &= ~SND_BRK;
		pmz_maybe_update_regs(uap);
	}

	spin_unlock_irqrestore(&port->lock, flags);

	/* Release interrupt handler */
	free_irq(uap->port.irq, uap);

	spin_lock_irqsave(&port->lock, flags);

	uap->flags &= ~PMACZILOG_FLAG_IS_OPEN;

	if (!ZS_IS_CONS(uap))
		pmz_set_scc_power(uap, 0);	/* Shut the chip down */

	spin_unlock_irqrestore(&port->lock, flags);

	pmz_debug("pmz: shutdown() done.\n");
}