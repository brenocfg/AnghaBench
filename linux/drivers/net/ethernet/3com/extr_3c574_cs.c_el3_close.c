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
struct pcmcia_device {int /*<<< orphan*/  open; int /*<<< orphan*/  dev; } ;
struct net_device {unsigned int base_addr; int /*<<< orphan*/  name; } ;
struct el3_private {int /*<<< orphan*/  media; int /*<<< orphan*/  window_lock; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL3WINDOW (int /*<<< orphan*/ ) ; 
 scalar_t__ EL3_CMD ; 
 int RxDisable ; 
 int SetIntrEnb ; 
 int StatsDisable ; 
 int TxDisable ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 scalar_t__ pcmcia_dev_present (struct pcmcia_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_stats (struct net_device*) ; 

__attribute__((used)) static int el3_close(struct net_device *dev)
{
	unsigned int ioaddr = dev->base_addr;
	struct el3_private *lp = netdev_priv(dev);
	struct pcmcia_device *link = lp->p_dev;

	dev_dbg(&link->dev, "%s: shutting down ethercard.\n", dev->name);
	
	if (pcmcia_dev_present(link)) {
		unsigned long flags;

		/* Turn off statistics ASAP.  We update lp->stats below. */
		outw(StatsDisable, ioaddr + EL3_CMD);
		
		/* Disable the receiver and transmitter. */
		outw(RxDisable, ioaddr + EL3_CMD);
		outw(TxDisable, ioaddr + EL3_CMD);
		
		/* Note: Switching to window 0 may disable the IRQ. */
		EL3WINDOW(0);
		spin_lock_irqsave(&lp->window_lock, flags);
		update_stats(dev);
		spin_unlock_irqrestore(&lp->window_lock, flags);

		/* force interrupts off */
		outw(SetIntrEnb | 0x0000, ioaddr + EL3_CMD);
	}

	link->open--;
	netif_stop_queue(dev);
	del_timer_sync(&lp->media);

	return 0;
}