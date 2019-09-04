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
struct net_device {int dummy; } ;
struct ks8695_priv {scalar_t__ phyiface_regs; } ;
struct TYPE_4__ {scalar_t__ speed; scalar_t__ duplex; scalar_t__ port; scalar_t__ autoneg; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 scalar_t__ KS8695_WMC ; 
 scalar_t__ PORT_MII ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int WMC_WANA100F ; 
 int WMC_WANA100H ; 
 int WMC_WANA10F ; 
 int WMC_WANA10H ; 
 int WMC_WAND ; 
 int WMC_WANF100 ; 
 int WMC_WANFF ; 
 int WMC_WANR ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int*,int /*<<< orphan*/ ) ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int
ks8695_wan_set_link_ksettings(struct net_device *ndev,
			      const struct ethtool_link_ksettings *cmd)
{
	struct ks8695_priv *ksp = netdev_priv(ndev);
	u32 ctrl;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	if ((cmd->base.speed != SPEED_10) && (cmd->base.speed != SPEED_100))
		return -EINVAL;
	if ((cmd->base.duplex != DUPLEX_HALF) &&
	    (cmd->base.duplex != DUPLEX_FULL))
		return -EINVAL;
	if (cmd->base.port != PORT_MII)
		return -EINVAL;
	if ((cmd->base.autoneg != AUTONEG_DISABLE) &&
	    (cmd->base.autoneg != AUTONEG_ENABLE))
		return -EINVAL;

	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		if ((advertising & (ADVERTISED_10baseT_Half |
				ADVERTISED_10baseT_Full |
				ADVERTISED_100baseT_Half |
				ADVERTISED_100baseT_Full)) == 0)
			return -EINVAL;

		ctrl = readl(ksp->phyiface_regs + KS8695_WMC);

		ctrl &= ~(WMC_WAND | WMC_WANA100F | WMC_WANA100H |
			  WMC_WANA10F | WMC_WANA10H);
		if (advertising & ADVERTISED_100baseT_Full)
			ctrl |= WMC_WANA100F;
		if (advertising & ADVERTISED_100baseT_Half)
			ctrl |= WMC_WANA100H;
		if (advertising & ADVERTISED_10baseT_Full)
			ctrl |= WMC_WANA10F;
		if (advertising & ADVERTISED_10baseT_Half)
			ctrl |= WMC_WANA10H;

		/* force a re-negotiation */
		ctrl |= WMC_WANR;
		writel(ctrl, ksp->phyiface_regs + KS8695_WMC);
	} else {
		ctrl = readl(ksp->phyiface_regs + KS8695_WMC);

		/* disable auto-negotiation */
		ctrl |= WMC_WAND;
		ctrl &= ~(WMC_WANF100 | WMC_WANFF);

		if (cmd->base.speed == SPEED_100)
			ctrl |= WMC_WANF100;
		if (cmd->base.duplex == DUPLEX_FULL)
			ctrl |= WMC_WANFF;

		writel(ctrl, ksp->phyiface_regs + KS8695_WMC);
	}

	return 0;
}