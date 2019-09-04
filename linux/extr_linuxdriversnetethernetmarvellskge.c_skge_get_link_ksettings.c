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
typedef  int /*<<< orphan*/  u32 ;
struct skge_port {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  advertising; struct skge_hw* hw; } ;
struct skge_hw {int /*<<< orphan*/  phy_addr; scalar_t__ copper; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  port; int /*<<< orphan*/  phy_address; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skge_supported_modes (struct skge_hw*) ; 

__attribute__((used)) static int skge_get_link_ksettings(struct net_device *dev,
				   struct ethtool_link_ksettings *cmd)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	u32 supported, advertising;

	supported = skge_supported_modes(hw);

	if (hw->copper) {
		cmd->base.port = PORT_TP;
		cmd->base.phy_address = hw->phy_addr;
	} else
		cmd->base.port = PORT_FIBRE;

	advertising = skge->advertising;
	cmd->base.autoneg = skge->autoneg;
	cmd->base.speed = skge->speed;
	cmd->base.duplex = skge->duplex;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}