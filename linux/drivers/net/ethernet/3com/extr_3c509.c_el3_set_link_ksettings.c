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
struct ethtool_link_ksettings {int dummy; } ;
struct el3_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int el3_netdev_set_ecmd (struct net_device*,struct ethtool_link_ksettings const*) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int el3_set_link_ksettings(struct net_device *dev,
				  const struct ethtool_link_ksettings *cmd)
{
	struct el3_private *lp = netdev_priv(dev);
	int ret;

	spin_lock_irq(&lp->lock);
	ret = el3_netdev_set_ecmd(dev, cmd);
	spin_unlock_irq(&lp->lock);
	return ret;
}