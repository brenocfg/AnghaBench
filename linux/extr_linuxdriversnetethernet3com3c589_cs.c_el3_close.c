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
struct net_device {unsigned int base_addr; int if_port; int /*<<< orphan*/  name; } ;
struct el3_private {int /*<<< orphan*/  media; struct pcmcia_device* p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 scalar_t__ EL3_CMD ; 
 scalar_t__ EL3_STATUS ; 
 int RxDisable ; 
 int StatsDisable ; 
 int StopCoax ; 
 int TxDisable ; 
 scalar_t__ WN0_IRQ ; 
 scalar_t__ WN4_MEDIA ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int inw (scalar_t__) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 scalar_t__ pcmcia_dev_present (struct pcmcia_device*) ; 
 int /*<<< orphan*/  update_stats (struct net_device*) ; 

__attribute__((used)) static int el3_close(struct net_device *dev)
{
	struct el3_private *lp = netdev_priv(dev);
	struct pcmcia_device *link = lp->p_dev;
	unsigned int ioaddr = dev->base_addr;

	dev_dbg(&link->dev, "%s: shutting down ethercard.\n", dev->name);

	if (pcmcia_dev_present(link)) {
		/* Turn off statistics ASAP.  We update dev->stats below. */
		outw(StatsDisable, ioaddr + EL3_CMD);

		/* Disable the receiver and transmitter. */
		outw(RxDisable, ioaddr + EL3_CMD);
		outw(TxDisable, ioaddr + EL3_CMD);

		if (dev->if_port == 2)
			/* Turn off thinnet power.  Green! */
			outw(StopCoax, ioaddr + EL3_CMD);
		else if (dev->if_port == 1) {
			/* Disable link beat and jabber */
			EL3WINDOW(4);
			outw(0, ioaddr + WN4_MEDIA);
		}

		/* Switching back to window 0 disables the IRQ. */
		EL3WINDOW(0);
		/* But we explicitly zero the IRQ line select anyway. */
		outw(0x0f00, ioaddr + WN0_IRQ);

		/* Check if the card still exists */
		if ((inw(ioaddr+EL3_STATUS) & 0xe000) == 0x2000)
			update_stats(dev);
	}

	link->open--;
	netif_stop_queue(dev);
	del_timer_sync(&lp->media);

	return 0;
}