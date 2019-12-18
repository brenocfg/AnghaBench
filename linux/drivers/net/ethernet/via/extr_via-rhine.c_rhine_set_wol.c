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
typedef  int u32 ;
struct rhine_private {int quirks; int wolopts; int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int EINVAL ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 
 int rqWOL ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rhine_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct rhine_private *rp = netdev_priv(dev);
	u32 support = WAKE_PHY | WAKE_MAGIC |
		      WAKE_UCAST | WAKE_MCAST | WAKE_BCAST;	/* Untested */

	if (!(rp->quirks & rqWOL))
		return -EINVAL;

	if (wol->wolopts & ~support)
		return -EINVAL;

	spin_lock_irq(&rp->lock);
	rp->wolopts = wol->wolopts;
	spin_unlock_irq(&rp->lock);

	return 0;
}