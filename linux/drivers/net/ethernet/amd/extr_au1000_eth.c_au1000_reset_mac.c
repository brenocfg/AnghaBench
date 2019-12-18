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
struct net_device {int dummy; } ;
struct au1000_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  au1000_reset_mac_unlocked (struct net_device*) ; 
 int /*<<< orphan*/  hw ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct au1000_private* const,int /*<<< orphan*/ ,struct net_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void au1000_reset_mac(struct net_device *dev)
{
	struct au1000_private *const aup = netdev_priv(dev);
	unsigned long flags;

	netif_dbg(aup, hw, dev, "reset mac, aup %x\n",
					(unsigned)aup);

	spin_lock_irqsave(&aup->lock, flags);

	au1000_reset_mac_unlocked(dev);

	spin_unlock_irqrestore(&aup->lock, flags);
}