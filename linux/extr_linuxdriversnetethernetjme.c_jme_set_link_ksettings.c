#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ speed; scalar_t__ autoneg; scalar_t__ duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct TYPE_4__ {scalar_t__ full_duplex; scalar_t__ force_media; } ;
struct jme_adapter {int /*<<< orphan*/  flags; struct ethtool_link_ksettings old_cmd; int /*<<< orphan*/  phy_lock; TYPE_2__ mii_if; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  JME_FLAG_SSET ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  jme_reset_link (struct jme_adapter*) ; 
 int mii_ethtool_set_link_ksettings (TYPE_2__*,struct ethtool_link_ksettings const*) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_set_link_ksettings(struct net_device *netdev,
		       const struct ethtool_link_ksettings *cmd)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	int rc, fdc = 0;

	if (cmd->base.speed == SPEED_1000 &&
	    cmd->base.autoneg != AUTONEG_ENABLE)
		return -EINVAL;

	/*
	 * Check If user changed duplex only while force_media.
	 * Hardware would not generate link change interrupt.
	 */
	if (jme->mii_if.force_media &&
	    cmd->base.autoneg != AUTONEG_ENABLE &&
	    (jme->mii_if.full_duplex != cmd->base.duplex))
		fdc = 1;

	spin_lock_bh(&jme->phy_lock);
	rc = mii_ethtool_set_link_ksettings(&jme->mii_if, cmd);
	spin_unlock_bh(&jme->phy_lock);

	if (!rc) {
		if (fdc)
			jme_reset_link(jme);
		jme->old_cmd = *cmd;
		set_bit(JME_FLAG_SSET, &jme->flags);
	}

	return rc;
}