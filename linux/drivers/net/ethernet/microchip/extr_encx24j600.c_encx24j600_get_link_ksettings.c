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
struct TYPE_4__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;
struct encx24j600_priv {scalar_t__ autoneg; scalar_t__ full_duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  PORT_TP ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct encx24j600_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int encx24j600_get_link_ksettings(struct net_device *dev,
					 struct ethtool_link_ksettings *cmd)
{
	struct encx24j600_priv *priv = netdev_priv(dev);
	u32 supported;

	supported = SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
			 SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
			 SUPPORTED_Autoneg | SUPPORTED_TP;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);

	cmd->base.speed = priv->speed;
	cmd->base.duplex = priv->full_duplex ? DUPLEX_FULL : DUPLEX_HALF;
	cmd->base.port = PORT_TP;
	cmd->base.autoneg = priv->autoneg ? AUTONEG_ENABLE : AUTONEG_DISABLE;

	return 0;
}