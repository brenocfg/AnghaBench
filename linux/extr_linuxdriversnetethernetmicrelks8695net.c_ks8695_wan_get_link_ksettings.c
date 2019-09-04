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
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {void* duplex; void* speed; int /*<<< orphan*/  autoneg; scalar_t__ phy_address; int /*<<< orphan*/  port; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_MII ; 
 int ADVERTISED_Pause ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 void* DUPLEX_FULL ; 
 void* DUPLEX_HALF ; 
 scalar_t__ KS8695_WMC ; 
 int /*<<< orphan*/  PORT_MII ; 
 void* SPEED_10 ; 
 void* SPEED_100 ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MII ; 
 int SUPPORTED_Pause ; 
 int SUPPORTED_TP ; 
 int WMC_WANA100F ; 
 int WMC_WANA100H ; 
 int WMC_WANA10F ; 
 int WMC_WANA10H ; 
 int WMC_WANAP ; 
 int WMC_WAND ; 
 int WMC_WANF100 ; 
 int WMC_WANFF ; 
 int WMC_WDS ; 
 int WMC_WSS ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int
ks8695_wan_get_link_ksettings(struct net_device *ndev,
			      struct ethtool_link_ksettings *cmd)
{
	struct ks8695_priv *ksp = netdev_priv(ndev);
	u32 ctrl;
	u32 supported, advertising;

	/* All ports on the KS8695 support these... */
	supported = (SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
			  SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
			  SUPPORTED_TP | SUPPORTED_MII);

	advertising = ADVERTISED_TP | ADVERTISED_MII;
	cmd->base.port = PORT_MII;
	supported |= (SUPPORTED_Autoneg | SUPPORTED_Pause);
	cmd->base.phy_address = 0;

	ctrl = readl(ksp->phyiface_regs + KS8695_WMC);
	if ((ctrl & WMC_WAND) == 0) {
		/* auto-negotiation is enabled */
		advertising |= ADVERTISED_Autoneg;
		if (ctrl & WMC_WANA100F)
			advertising |= ADVERTISED_100baseT_Full;
		if (ctrl & WMC_WANA100H)
			advertising |= ADVERTISED_100baseT_Half;
		if (ctrl & WMC_WANA10F)
			advertising |= ADVERTISED_10baseT_Full;
		if (ctrl & WMC_WANA10H)
			advertising |= ADVERTISED_10baseT_Half;
		if (ctrl & WMC_WANAP)
			advertising |= ADVERTISED_Pause;
		cmd->base.autoneg = AUTONEG_ENABLE;

		cmd->base.speed = (ctrl & WMC_WSS) ? SPEED_100 : SPEED_10;
		cmd->base.duplex = (ctrl & WMC_WDS) ?
			DUPLEX_FULL : DUPLEX_HALF;
	} else {
		/* auto-negotiation is disabled */
		cmd->base.autoneg = AUTONEG_DISABLE;

		cmd->base.speed = (ctrl & WMC_WANF100) ?
					    SPEED_100 : SPEED_10;
		cmd->base.duplex = (ctrl & WMC_WANFF) ?
			DUPLEX_FULL : DUPLEX_HALF;
	}

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}