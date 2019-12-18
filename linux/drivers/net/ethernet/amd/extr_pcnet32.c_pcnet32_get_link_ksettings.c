#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcnet32_private {scalar_t__ chip_version; int /*<<< orphan*/  lock; scalar_t__ fdx; scalar_t__ port_tp; TYPE_1__* a; scalar_t__ autoneg; int /*<<< orphan*/  mii_if; scalar_t__ mii; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  supported; } ;
struct TYPE_5__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; void* port; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_3__ link_modes; TYPE_2__ base; } ;
struct TYPE_4__ {int (* read_bcr ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 scalar_t__ PCNET32_79C970A ; 
 void* PORT_AUI ; 
 void* PORT_TP ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcnet32_get_link_ksettings(struct net_device *dev,
				      struct ethtool_link_ksettings *cmd)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&lp->lock, flags);
	if (lp->mii) {
		mii_ethtool_get_link_ksettings(&lp->mii_if, cmd);
	} else if (lp->chip_version == PCNET32_79C970A) {
		if (lp->autoneg) {
			cmd->base.autoneg = AUTONEG_ENABLE;
			if (lp->a->read_bcr(dev->base_addr, 4) == 0xc0)
				cmd->base.port = PORT_AUI;
			else
				cmd->base.port = PORT_TP;
		} else {
			cmd->base.autoneg = AUTONEG_DISABLE;
			cmd->base.port = lp->port_tp ? PORT_TP : PORT_AUI;
		}
		cmd->base.duplex = lp->fdx ? DUPLEX_FULL : DUPLEX_HALF;
		cmd->base.speed = SPEED_10;
		ethtool_convert_legacy_u32_to_link_mode(
						cmd->link_modes.supported,
						SUPPORTED_TP | SUPPORTED_AUI);
	}
	spin_unlock_irqrestore(&lp->lock, flags);
	return 0;
}