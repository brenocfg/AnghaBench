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
struct jme_adapter {int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  mii_if; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_get_link_ksettings(struct net_device *netdev,
		       struct ethtool_link_ksettings *cmd)
{
	struct jme_adapter *jme = netdev_priv(netdev);

	spin_lock_bh(&jme->phy_lock);
	mii_ethtool_get_link_ksettings(&jme->mii_if, cmd);
	spin_unlock_bh(&jme->phy_lock);
	return 0;
}