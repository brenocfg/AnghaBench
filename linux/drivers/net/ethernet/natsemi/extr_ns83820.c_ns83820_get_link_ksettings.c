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
struct ns83820 {int CFG_cache; scalar_t__ base; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; int /*<<< orphan*/  port; } ;
struct TYPE_3__ {int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 scalar_t__ CFG ; 
 int CFG_DUPSTS ; 
 int CFG_SPDSTS0 ; 
 int CFG_TBI_EN ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_MII ; 
 struct ns83820* PRIV (struct net_device*) ; 
 int SPDSTS_POLARITY ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_MII ; 
 scalar_t__ TANAR ; 
 scalar_t__ TBICR ; 
 int TBICR_MR_AN_ENABLE ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int ns83820_get_link_ksettings(struct net_device *ndev,
				      struct ethtool_link_ksettings *cmd)
{
	struct ns83820 *dev = PRIV(ndev);
	u32 cfg, tanar, tbicr;
	int fullduplex   = 0;
	u32 supported;

	/*
	 * Here's the list of available ethtool commands from other drivers:
	 *	cmd->advertising =
	 *	ethtool_cmd_speed_set(cmd, ...)
	 *	cmd->duplex =
	 *	cmd->port = 0;
	 *	cmd->phy_address =
	 *	cmd->transceiver = 0;
	 *	cmd->autoneg =
	 *	cmd->maxtxpkt = 0;
	 *	cmd->maxrxpkt = 0;
	 */

	/* read current configuration */
	cfg   = readl(dev->base + CFG) ^ SPDSTS_POLARITY;
	tanar = readl(dev->base + TANAR);
	tbicr = readl(dev->base + TBICR);

	fullduplex = (cfg & CFG_DUPSTS) ? 1 : 0;

	supported = SUPPORTED_Autoneg;

	if (dev->CFG_cache & CFG_TBI_EN) {
		/* we have optical interface */
		supported |= SUPPORTED_1000baseT_Half |
					SUPPORTED_1000baseT_Full |
					SUPPORTED_FIBRE;
		cmd->base.port       = PORT_FIBRE;
	} else {
		/* we have copper */
		supported |= SUPPORTED_10baseT_Half |
			SUPPORTED_10baseT_Full | SUPPORTED_100baseT_Half |
			SUPPORTED_100baseT_Full | SUPPORTED_1000baseT_Half |
			SUPPORTED_1000baseT_Full |
			SUPPORTED_MII;
		cmd->base.port = PORT_MII;
	}

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);

	cmd->base.duplex = fullduplex ? DUPLEX_FULL : DUPLEX_HALF;
	switch (cfg / CFG_SPDSTS0 & 3) {
	case 2:
		cmd->base.speed = SPEED_1000;
		break;
	case 1:
		cmd->base.speed = SPEED_100;
		break;
	default:
		cmd->base.speed = SPEED_10;
		break;
	}
	cmd->base.autoneg = (tbicr & TBICR_MR_AN_ENABLE)
		? AUTONEG_ENABLE : AUTONEG_DISABLE;
	return 0;
}