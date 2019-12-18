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
struct smc_local {scalar_t__ phy_type; int /*<<< orphan*/  lock; int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int mii_nway_restart (int /*<<< orphan*/ *) ; 
 struct smc_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smc_ethtool_nwayreset(struct net_device *dev)
{
	struct smc_local *lp = netdev_priv(dev);
	int ret = -EINVAL;

	if (lp->phy_type != 0) {
		spin_lock_irq(&lp->lock);
		ret = mii_nway_restart(&lp->mii);
		spin_unlock_irq(&lp->lock);
	}

	return ret;
}