#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  cmd; } ;
struct TYPE_13__ {int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_7__ base; TYPE_6__ link_modes; } ;
struct TYPE_12__ {int link_status; int /*<<< orphan*/  line_speed; int /*<<< orphan*/  duplex; scalar_t__ link_up; } ;
struct TYPE_11__ {scalar_t__* req_line_speed; TYPE_2__* phy; } ;
struct TYPE_10__ {int /*<<< orphan*/  prtad; } ;
struct TYPE_8__ {scalar_t__* supported; scalar_t__* advertising; } ;
struct bnx2x {scalar_t__ state; int flags; TYPE_5__ link_vars; TYPE_4__ link_params; TYPE_3__ mdio; TYPE_1__ port; } ;
struct TYPE_9__ {scalar_t__ media_type; } ;

/* Variables and functions */
 scalar_t__ ADVERTISED_10000baseKR_Full ; 
 scalar_t__ ADVERTISED_10000baseT_Full ; 
 scalar_t__ ADVERTISED_1000baseKX_Full ; 
 scalar_t__ ADVERTISED_1000baseT_Full ; 
 scalar_t__ ADVERTISED_1000baseT_Half ; 
 scalar_t__ ADVERTISED_100baseT_Full ; 
 scalar_t__ ADVERTISED_100baseT_Half ; 
 scalar_t__ ADVERTISED_10baseT_Full ; 
 scalar_t__ ADVERTISED_10baseT_Half ; 
 scalar_t__ ADVERTISED_20000baseKR2_Full ; 
 scalar_t__ ADVERTISED_2500baseX_Full ; 
 scalar_t__ ADVERTISED_Asym_Pause ; 
 scalar_t__ ADVERTISED_Autoneg ; 
 scalar_t__ ADVERTISED_Pause ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 scalar_t__ BNX2X_STATE_OPEN ; 
 int /*<<< orphan*/  BP_NOMCP (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 scalar_t__ ETH_PHY_KR ; 
 scalar_t__ ETH_PHY_SFP_1G_FIBER ; 
 scalar_t__ IS_MF (struct bnx2x*) ; 
 int LINK_STATUS_AUTO_NEGOTIATE_COMPLETE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_10THD_CAPABLE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_20GXFD_CAPABLE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE ; 
 scalar_t__ LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE ; 
 int MF_FUNC_DIS ; 
 scalar_t__ SPEED_AUTO_NEG ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 scalar_t__ SUPPORTED_10000baseT_Full ; 
 scalar_t__ SUPPORTED_FIBRE ; 
 scalar_t__ SUPPORTED_TP ; 
 size_t bnx2x_get_cur_phy_idx (struct bnx2x*) ; 
 int bnx2x_get_link_cfg_idx (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_get_mf_speed (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_get_port_type (struct bnx2x*) ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_get_link_ksettings(struct net_device *dev,
				    struct ethtool_link_ksettings *cmd)
{
	struct bnx2x *bp = netdev_priv(dev);
	int cfg_idx = bnx2x_get_link_cfg_idx(bp);
	u32 media_type;
	u32 supported, advertising, lp_advertising;

	ethtool_convert_link_mode_to_legacy_u32(&lp_advertising,
						cmd->link_modes.lp_advertising);

	/* Dual Media boards present all available port types */
	supported = bp->port.supported[cfg_idx] |
		(bp->port.supported[cfg_idx ^ 1] &
		 (SUPPORTED_TP | SUPPORTED_FIBRE));
	advertising = bp->port.advertising[cfg_idx];
	media_type = bp->link_params.phy[bnx2x_get_cur_phy_idx(bp)].media_type;
	if (media_type == ETH_PHY_SFP_1G_FIBER) {
		supported &= ~(SUPPORTED_10000baseT_Full);
		advertising &= ~(ADVERTISED_10000baseT_Full);
	}

	if ((bp->state == BNX2X_STATE_OPEN) && bp->link_vars.link_up &&
	    !(bp->flags & MF_FUNC_DIS)) {
		cmd->base.duplex = bp->link_vars.duplex;

		if (IS_MF(bp) && !BP_NOMCP(bp))
			cmd->base.speed = bnx2x_get_mf_speed(bp);
		else
			cmd->base.speed = bp->link_vars.line_speed;
	} else {
		cmd->base.duplex = DUPLEX_UNKNOWN;
		cmd->base.speed = SPEED_UNKNOWN;
	}

	cmd->base.port = bnx2x_get_port_type(bp);

	cmd->base.phy_address = bp->mdio.prtad;

	if (bp->link_params.req_line_speed[cfg_idx] == SPEED_AUTO_NEG)
		cmd->base.autoneg = AUTONEG_ENABLE;
	else
		cmd->base.autoneg = AUTONEG_DISABLE;

	/* Publish LP advertised speeds and FC */
	if (bp->link_vars.link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) {
		u32 status = bp->link_vars.link_status;

		lp_advertising |= ADVERTISED_Autoneg;
		if (status & LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE)
			lp_advertising |= ADVERTISED_Pause;
		if (status & LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE)
			lp_advertising |= ADVERTISED_Asym_Pause;

		if (status & LINK_STATUS_LINK_PARTNER_10THD_CAPABLE)
			lp_advertising |= ADVERTISED_10baseT_Half;
		if (status & LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE)
			lp_advertising |= ADVERTISED_10baseT_Full;
		if (status & LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE)
			lp_advertising |= ADVERTISED_100baseT_Half;
		if (status & LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE)
			lp_advertising |= ADVERTISED_100baseT_Full;
		if (status & LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE)
			lp_advertising |= ADVERTISED_1000baseT_Half;
		if (status & LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE) {
			if (media_type == ETH_PHY_KR) {
				lp_advertising |=
					ADVERTISED_1000baseKX_Full;
			} else {
				lp_advertising |=
					ADVERTISED_1000baseT_Full;
			}
		}
		if (status & LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE)
			lp_advertising |= ADVERTISED_2500baseX_Full;
		if (status & LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE) {
			if (media_type == ETH_PHY_KR) {
				lp_advertising |=
					ADVERTISED_10000baseKR_Full;
			} else {
				lp_advertising |=
					ADVERTISED_10000baseT_Full;
			}
		}
		if (status & LINK_STATUS_LINK_PARTNER_20GXFD_CAPABLE)
			lp_advertising |= ADVERTISED_20000baseKR2_Full;
	}

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.lp_advertising,
						lp_advertising);

	DP(BNX2X_MSG_ETHTOOL, "ethtool_cmd: cmd %d\n"
	   "  supported 0x%x  advertising 0x%x  speed %u\n"
	   "  duplex %d  port %d  phy_address %d\n"
	   "  autoneg %d\n",
	   cmd->base.cmd, supported, advertising,
	   cmd->base.speed,
	   cmd->base.duplex, cmd->base.port, cmd->base.phy_address,
	   cmd->base.autoneg);

	return 0;
}