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
struct mv643xx_eth_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int speed; int /*<<< orphan*/  autoneg; scalar_t__ phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int ADVERTISED_MII ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int FULL_DUPLEX ; 
 int /*<<< orphan*/  PORT_MII ; 
#define  PORT_SPEED_10 130 
#define  PORT_SPEED_100 129 
#define  PORT_SPEED_1000 128 
 int PORT_SPEED_MASK ; 
 int /*<<< orphan*/  PORT_STATUS ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SUPPORTED_MII ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv643xx_eth_get_link_ksettings_phyless(struct mv643xx_eth_private *mp,
				       struct ethtool_link_ksettings *cmd)
{
	u32 port_status;
	u32 supported, advertising;

	port_status = rdlp(mp, PORT_STATUS);

	supported = SUPPORTED_MII;
	advertising = ADVERTISED_MII;
	switch (port_status & PORT_SPEED_MASK) {
	case PORT_SPEED_10:
		cmd->base.speed = SPEED_10;
		break;
	case PORT_SPEED_100:
		cmd->base.speed = SPEED_100;
		break;
	case PORT_SPEED_1000:
		cmd->base.speed = SPEED_1000;
		break;
	default:
		cmd->base.speed = -1;
		break;
	}
	cmd->base.duplex = (port_status & FULL_DUPLEX) ?
		DUPLEX_FULL : DUPLEX_HALF;
	cmd->base.port = PORT_MII;
	cmd->base.phy_address = 0;
	cmd->base.autoneg = AUTONEG_DISABLE;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}