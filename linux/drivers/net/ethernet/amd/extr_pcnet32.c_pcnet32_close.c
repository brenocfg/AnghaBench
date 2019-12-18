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
struct pcnet32_private {int /*<<< orphan*/  lock; TYPE_2__* a; int /*<<< orphan*/  napi; int /*<<< orphan*/  watchdog_timer; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_missed_errors; } ;
struct net_device {unsigned long base_addr; int /*<<< orphan*/  irq; TYPE_1__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write_bcr ) (unsigned long,int,int) ;int /*<<< orphan*/  (* write_csr ) (unsigned long,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read_csr ) (unsigned long,int) ;} ;

/* Variables and functions */
 int CSR0 ; 
 int /*<<< orphan*/  CSR0_STOP ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_printk (struct pcnet32_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pcnet32_purge_rx_ring (struct net_device*) ; 
 int /*<<< orphan*/  pcnet32_purge_tx_ring (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (unsigned long,int) ; 
 int /*<<< orphan*/  stub2 (unsigned long,int) ; 
 int /*<<< orphan*/  stub3 (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (unsigned long,int,int) ; 

__attribute__((used)) static int pcnet32_close(struct net_device *dev)
{
	unsigned long ioaddr = dev->base_addr;
	struct pcnet32_private *lp = netdev_priv(dev);
	unsigned long flags;

	del_timer_sync(&lp->watchdog_timer);

	netif_stop_queue(dev);
	napi_disable(&lp->napi);

	spin_lock_irqsave(&lp->lock, flags);

	dev->stats.rx_missed_errors = lp->a->read_csr(ioaddr, 112);

	netif_printk(lp, ifdown, KERN_DEBUG, dev,
		     "Shutting down ethercard, status was %2.2x\n",
		     lp->a->read_csr(ioaddr, CSR0));

	/* We stop the PCNET32 here -- it occasionally polls memory if we don't. */
	lp->a->write_csr(ioaddr, CSR0, CSR0_STOP);

	/*
	 * Switch back to 16bit mode to avoid problems with dumb
	 * DOS packet driver after a warm reboot
	 */
	lp->a->write_bcr(ioaddr, 20, 4);

	spin_unlock_irqrestore(&lp->lock, flags);

	free_irq(dev->irq, dev);

	spin_lock_irqsave(&lp->lock, flags);

	pcnet32_purge_rx_ring(dev);
	pcnet32_purge_tx_ring(dev);

	spin_unlock_irqrestore(&lp->lock, flags);

	return 0;
}