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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_3__* state; TYPE_1__ icount; } ;
struct mctrl_gpios {int mctrl_prev; struct uart_port* port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_6__ {TYPE_2__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MCTRL_ANY_DELTA ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_RI ; 
 int /*<<< orphan*/  mctrl_gpio_get (struct mctrl_gpios*,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uart_handle_cts_change (struct uart_port*,int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (struct uart_port*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mctrl_gpio_irq_handle(int irq, void *context)
{
	struct mctrl_gpios *gpios = context;
	struct uart_port *port = gpios->port;
	u32 mctrl = gpios->mctrl_prev;
	u32 mctrl_diff;
	unsigned long flags;

	mctrl_gpio_get(gpios, &mctrl);

	spin_lock_irqsave(&port->lock, flags);

	mctrl_diff = mctrl ^ gpios->mctrl_prev;
	gpios->mctrl_prev = mctrl;

	if (mctrl_diff & MCTRL_ANY_DELTA && port->state != NULL) {
		if ((mctrl_diff & mctrl) & TIOCM_RI)
			port->icount.rng++;

		if ((mctrl_diff & mctrl) & TIOCM_DSR)
			port->icount.dsr++;

		if (mctrl_diff & TIOCM_CD)
			uart_handle_dcd_change(port, mctrl & TIOCM_CD);

		if (mctrl_diff & TIOCM_CTS)
			uart_handle_cts_change(port, mctrl & TIOCM_CTS);

		wake_up_interruptible(&port->state->port.delta_msr_wait);
	}

	spin_unlock_irqrestore(&port->lock, flags);

	return IRQ_HANDLED;
}