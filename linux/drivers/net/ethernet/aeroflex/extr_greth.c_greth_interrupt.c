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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct greth_private {int /*<<< orphan*/  devlock; int /*<<< orphan*/  napi; TYPE_1__* regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  control; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int GRETH_INT_RE ; 
 int GRETH_INT_RX ; 
 int GRETH_INT_TE ; 
 int GRETH_INT_TX ; 
 int GRETH_REGLOAD (int /*<<< orphan*/ ) ; 
 int GRETH_RXI ; 
 int GRETH_TXI ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  greth_disable_irqs (struct greth_private*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct greth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t greth_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	struct greth_private *greth;
	u32 status, ctrl;
	irqreturn_t retval = IRQ_NONE;

	greth = netdev_priv(dev);

	spin_lock(&greth->devlock);

	/* Get the interrupt events that caused us to be here. */
	status = GRETH_REGLOAD(greth->regs->status);

	/* Must see if interrupts are enabled also, INT_TX|INT_RX flags may be
	 * set regardless of whether IRQ is enabled or not. Especially
	 * important when shared IRQ.
	 */
	ctrl = GRETH_REGLOAD(greth->regs->control);

	/* Handle rx and tx interrupts through poll */
	if (((status & (GRETH_INT_RE | GRETH_INT_RX)) && (ctrl & GRETH_RXI)) ||
	    ((status & (GRETH_INT_TE | GRETH_INT_TX)) && (ctrl & GRETH_TXI))) {
		retval = IRQ_HANDLED;

		/* Disable interrupts and schedule poll() */
		greth_disable_irqs(greth);
		napi_schedule(&greth->napi);
	}

	spin_unlock(&greth->devlock);

	return retval;
}