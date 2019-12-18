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
struct ethtool_wolinfo {int /*<<< orphan*/  sopass; int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_get_sopass (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_get_wol (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct netdev_private *np = netdev_priv(dev);
	spin_lock_irq(&np->lock);
	netdev_get_wol(dev, &wol->supported, &wol->wolopts);
	netdev_get_sopass(dev, wol->sopass);
	spin_unlock_irq(&np->lock);
}