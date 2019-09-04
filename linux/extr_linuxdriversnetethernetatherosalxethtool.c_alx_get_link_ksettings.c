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
struct TYPE_3__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; scalar_t__ phy_address; int /*<<< orphan*/  port; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;
struct alx_hw {int adv_cfg; int flowctrl; int /*<<< orphan*/  duplex; int /*<<< orphan*/  link_speed; } ;
struct alx_priv {struct alx_hw hw; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_Pause ; 
 int ADVERTISED_TP ; 
 int ALX_FC_ANEG ; 
 int ALX_FC_RX ; 
 int ALX_FC_TX ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_Pause ; 
 int SUPPORTED_TP ; 
 int alx_get_supported_speeds (struct alx_hw*) ; 
 scalar_t__ alx_hw_giga (struct alx_hw*) ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int alx_get_link_ksettings(struct net_device *netdev,
				  struct ethtool_link_ksettings *cmd)
{
	struct alx_priv *alx = netdev_priv(netdev);
	struct alx_hw *hw = &alx->hw;
	u32 supported, advertising;

	supported = SUPPORTED_Autoneg |
			  SUPPORTED_TP |
			  SUPPORTED_Pause |
			  SUPPORTED_Asym_Pause;
	if (alx_hw_giga(hw))
		supported |= SUPPORTED_1000baseT_Full;
	supported |= alx_get_supported_speeds(hw);

	advertising = ADVERTISED_TP;
	if (hw->adv_cfg & ADVERTISED_Autoneg)
		advertising |= hw->adv_cfg;

	cmd->base.port = PORT_TP;
	cmd->base.phy_address = 0;

	if (hw->adv_cfg & ADVERTISED_Autoneg)
		cmd->base.autoneg = AUTONEG_ENABLE;
	else
		cmd->base.autoneg = AUTONEG_DISABLE;

	if (hw->flowctrl & ALX_FC_ANEG && hw->adv_cfg & ADVERTISED_Autoneg) {
		if (hw->flowctrl & ALX_FC_RX) {
			advertising |= ADVERTISED_Pause;

			if (!(hw->flowctrl & ALX_FC_TX))
				advertising |= ADVERTISED_Asym_Pause;
		} else if (hw->flowctrl & ALX_FC_TX) {
			advertising |= ADVERTISED_Asym_Pause;
		}
	}

	cmd->base.speed = hw->link_speed;
	cmd->base.duplex = hw->duplex;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}