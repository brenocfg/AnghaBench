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
typedef  int u32 ;
struct smc_local {scalar_t__ phy_type; int ctl_rspeed; int tcr_cur_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  duplex; scalar_t__ port; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_TP ; 
 int TCR_SWFDUP ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 struct smc_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smc_ethtool_get_link_ksettings(struct net_device *dev,
			       struct ethtool_link_ksettings *cmd)
{
	struct smc_local *lp = netdev_priv(dev);

	if (lp->phy_type != 0) {
		spin_lock_irq(&lp->lock);
		mii_ethtool_get_link_ksettings(&lp->mii, cmd);
		spin_unlock_irq(&lp->lock);
	} else {
		u32 supported = SUPPORTED_10baseT_Half |
				 SUPPORTED_10baseT_Full |
				 SUPPORTED_TP | SUPPORTED_AUI;

		if (lp->ctl_rspeed == 10)
			cmd->base.speed = SPEED_10;
		else if (lp->ctl_rspeed == 100)
			cmd->base.speed = SPEED_100;

		cmd->base.autoneg = AUTONEG_DISABLE;
		cmd->base.port = 0;
		cmd->base.duplex = lp->tcr_cur_mode & TCR_SWFDUP ?
			DUPLEX_FULL : DUPLEX_HALF;

		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported, supported);
	}

	return 0;
}