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
struct korina_private {int /*<<< orphan*/  mii_if; int /*<<< orphan*/  lock; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  korina_set_carrier (int /*<<< orphan*/ *) ; 
 int mii_ethtool_set_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings const*) ; 
 struct korina_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netdev_set_link_ksettings(struct net_device *dev,
				     const struct ethtool_link_ksettings *cmd)
{
	struct korina_private *lp = netdev_priv(dev);
	int rc;

	spin_lock_irq(&lp->lock);
	rc = mii_ethtool_set_link_ksettings(&lp->mii_if, cmd);
	spin_unlock_irq(&lp->lock);
	korina_set_carrier(&lp->mii_if);

	return rc;
}