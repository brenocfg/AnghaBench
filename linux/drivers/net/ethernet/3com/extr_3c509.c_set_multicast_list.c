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
struct net_device {int base_addr; int flags; int /*<<< orphan*/  name; } ;
struct el3_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ EL3_CMD ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int RxBroadcast ; 
 int RxMulticast ; 
 int RxProm ; 
 int RxStation ; 
 int SetRxFilter ; 
 int el3_debug ; 
 int netdev_mc_count (struct net_device*) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
set_multicast_list(struct net_device *dev)
{
	unsigned long flags;
	struct el3_private *lp = netdev_priv(dev);
	int ioaddr = dev->base_addr;
	int mc_count = netdev_mc_count(dev);

	if (el3_debug > 1) {
		static int old;
		if (old != mc_count) {
			old = mc_count;
			pr_debug("%s: Setting Rx mode to %d addresses.\n",
				 dev->name, mc_count);
		}
	}
	spin_lock_irqsave(&lp->lock, flags);
	if (dev->flags&IFF_PROMISC) {
		outw(SetRxFilter | RxStation | RxMulticast | RxBroadcast | RxProm,
			 ioaddr + EL3_CMD);
	}
	else if (mc_count || (dev->flags&IFF_ALLMULTI)) {
		outw(SetRxFilter | RxStation | RxMulticast | RxBroadcast, ioaddr + EL3_CMD);
	}
	else
		outw(SetRxFilter | RxStation | RxBroadcast, ioaddr + EL3_CMD);
	spin_unlock_irqrestore(&lp->lock, flags);
}