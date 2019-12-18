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
struct sgiseeq_regs {int dummy; } ;
struct sgiseeq_private {scalar_t__ tx_old; scalar_t__ tx_new; int /*<<< orphan*/  tx_lock; struct sgiseeq_regs* sregs; struct hpc3_ethregs* hregs; } ;
struct net_device {int dummy; } ;
struct hpc3_ethregs {int /*<<< orphan*/  reset; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HPC3_ERST_CLRIRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TX_BUFFS_AVAIL (struct sgiseeq_private*) ; 
 struct sgiseeq_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  sgiseeq_rx (struct net_device*,struct sgiseeq_private*,struct hpc3_ethregs*,struct sgiseeq_regs*) ; 
 int /*<<< orphan*/  sgiseeq_tx (struct net_device*,struct sgiseeq_private*,struct hpc3_ethregs*,struct sgiseeq_regs*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sgiseeq_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *) dev_id;
	struct sgiseeq_private *sp = netdev_priv(dev);
	struct hpc3_ethregs *hregs = sp->hregs;
	struct sgiseeq_regs *sregs = sp->sregs;

	spin_lock(&sp->tx_lock);

	/* Ack the IRQ and set software state. */
	hregs->reset = HPC3_ERST_CLRIRQ;

	/* Always check for received packets. */
	sgiseeq_rx(dev, sp, hregs, sregs);

	/* Only check for tx acks if we have something queued. */
	if (sp->tx_old != sp->tx_new)
		sgiseeq_tx(dev, sp, hregs, sregs);

	if ((TX_BUFFS_AVAIL(sp) > 0) && netif_queue_stopped(dev)) {
		netif_wake_queue(dev);
	}
	spin_unlock(&sp->tx_lock);

	return IRQ_HANDLED;
}