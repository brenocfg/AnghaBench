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
struct netdev_private {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  sopass; int /*<<< orphan*/  wolopts; } ;

/* Variables and functions */
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int netdev_set_sopass (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_set_wol (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct netdev_private *np = netdev_priv(dev);
	int res;
	spin_lock_irq(&np->lock);
	netdev_set_wol(dev, wol->wolopts);
	res = netdev_set_sopass(dev, wol->sopass);
	spin_unlock_irq(&np->lock);
	return res;
}