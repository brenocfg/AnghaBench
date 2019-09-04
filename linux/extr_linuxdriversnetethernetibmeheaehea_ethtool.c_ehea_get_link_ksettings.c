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
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;
struct ehea_port {int port_speed; int full_duplex; int autoneg; } ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
#define  EHEA_SPEED_100M 131 
#define  EHEA_SPEED_10G 130 
#define  EHEA_SPEED_10M 129 
#define  EHEA_SPEED_1G 128 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SPEED_10000 ; 
 int SPEED_UNKNOWN ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_TP ; 
 int ehea_sense_port_attr (struct ehea_port*) ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct ehea_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int ehea_get_link_ksettings(struct net_device *dev,
				   struct ethtool_link_ksettings *cmd)
{
	struct ehea_port *port = netdev_priv(dev);
	u32 supported, advertising;
	u32 speed;
	int ret;

	ret = ehea_sense_port_attr(port);

	if (ret)
		return ret;

	if (netif_carrier_ok(dev)) {
		switch (port->port_speed) {
		case EHEA_SPEED_10M:
			speed = SPEED_10;
			break;
		case EHEA_SPEED_100M:
			speed = SPEED_100;
			break;
		case EHEA_SPEED_1G:
			speed = SPEED_1000;
			break;
		case EHEA_SPEED_10G:
			speed = SPEED_10000;
			break;
		default:
			speed = -1;
			break; /* BUG */
		}
		cmd->base.duplex = port->full_duplex == 1 ?
						     DUPLEX_FULL : DUPLEX_HALF;
	} else {
		speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	}
	cmd->base.speed = speed;

	if (cmd->base.speed == SPEED_10000) {
		supported = (SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE);
		advertising = (ADVERTISED_10000baseT_Full | ADVERTISED_FIBRE);
		cmd->base.port = PORT_FIBRE;
	} else {
		supported = (SUPPORTED_1000baseT_Full | SUPPORTED_100baseT_Full
			       | SUPPORTED_100baseT_Half | SUPPORTED_10baseT_Full
			       | SUPPORTED_10baseT_Half | SUPPORTED_Autoneg
			       | SUPPORTED_TP);
		advertising = (ADVERTISED_1000baseT_Full | ADVERTISED_Autoneg
				 | ADVERTISED_TP);
		cmd->base.port = PORT_TP;
	}

	cmd->base.autoneg = port->autoneg == 1 ?
		AUTONEG_ENABLE : AUTONEG_DISABLE;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}