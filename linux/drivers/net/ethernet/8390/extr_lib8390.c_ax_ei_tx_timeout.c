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
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct net_device {unsigned long base_addr; int /*<<< orphan*/  irq; TYPE_1__ stats; } ;
struct ei_device {int interface_num; int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 scalar_t__ EN0_ISR ; 
 scalar_t__ EN0_TSR ; 
 int ENTSR_ABT ; 
 int /*<<< orphan*/  __NS8390_init (struct net_device*,int) ; 
 int dev_trans_start (struct net_device*) ; 
 int /*<<< orphan*/  disable_irq_nosync_lockdep (int /*<<< orphan*/ ) ; 
 int ei_inb (scalar_t__) ; 
 int /*<<< orphan*/  ei_reset_8390 (struct net_device*) ; 
 int /*<<< orphan*/  enable_irq_lockdep (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,char*,int,int,int) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __ei_tx_timeout(struct net_device *dev)
{
	unsigned long e8390_base = dev->base_addr;
	struct ei_device *ei_local = netdev_priv(dev);
	int txsr, isr, tickssofar = jiffies - dev_trans_start(dev);
	unsigned long flags;

	dev->stats.tx_errors++;

	spin_lock_irqsave(&ei_local->page_lock, flags);
	txsr = ei_inb(e8390_base+EN0_TSR);
	isr = ei_inb(e8390_base+EN0_ISR);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);

	netdev_dbg(dev, "Tx timed out, %s TSR=%#2x, ISR=%#2x, t=%d\n",
		   (txsr & ENTSR_ABT) ? "excess collisions." :
		   (isr) ? "lost interrupt?" : "cable problem?",
		   txsr, isr, tickssofar);

	if (!isr && !dev->stats.tx_packets) {
		/* The 8390 probably hasn't gotten on the cable yet. */
		ei_local->interface_num ^= 1;   /* Try a different xcvr.  */
	}

	/* Ugly but a reset can be slow, yet must be protected */

	disable_irq_nosync_lockdep(dev->irq);
	spin_lock(&ei_local->page_lock);

	/* Try to restart the card.  Perhaps the user has fixed something. */
	ei_reset_8390(dev);
	__NS8390_init(dev, 1);

	spin_unlock(&ei_local->page_lock);
	enable_irq_lockdep(dev->irq);
	netif_wake_queue(dev);
}