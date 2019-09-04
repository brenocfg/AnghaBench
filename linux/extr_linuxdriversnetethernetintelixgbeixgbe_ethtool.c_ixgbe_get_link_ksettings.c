#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_10__ {int requested_mode; } ;
struct TYPE_9__ {int autoneg_advertised; int type; int /*<<< orphan*/  sfp_type; scalar_t__ multispeed_fiber; int /*<<< orphan*/  media_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_link_capabilities ) (struct ixgbe_hw*,int*,int*) ;} ;
struct TYPE_8__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ fc; TYPE_3__ phy; TYPE_2__ mac; } ;
struct ixgbe_adapter {int link_speed; struct ixgbe_hw hw; } ;
struct TYPE_12__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_11__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; void* port; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_6__ link_modes; TYPE_5__ base; } ;
typedef  int ixgbe_link_speed ;

/* Variables and functions */
 int ADVERTISED_10000baseT_Full ; 
 int ADVERTISED_1000baseKX_Full ; 
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_Pause ; 
 int ADVERTISED_TP ; 
 int ADVRTSD_MSK_10G ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
#define  IXGBE_LINK_SPEED_100_FULL 172 
#define  IXGBE_LINK_SPEED_10GB_FULL 171 
#define  IXGBE_LINK_SPEED_10_FULL 170 
#define  IXGBE_LINK_SPEED_1GB_FULL 169 
#define  IXGBE_LINK_SPEED_2_5GB_FULL 168 
#define  IXGBE_LINK_SPEED_5GB_FULL 167 
 void* PORT_DA ; 
 void* PORT_FIBRE ; 
 void* PORT_NONE ; 
 void* PORT_OTHER ; 
 void* PORT_TP ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int /*<<< orphan*/  SPEED_5000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int SUPPORTED_1000baseKX_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_Pause ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int*,int /*<<< orphan*/ ) ; 
#define  ixgbe_fc_full 166 
#define  ixgbe_fc_rx_pause 165 
#define  ixgbe_fc_tx_pause 164 
 int ixgbe_get_supported_10gtypes (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_isbackplane (int /*<<< orphan*/ ) ; 
#define  ixgbe_phy_aq 163 
#define  ixgbe_phy_cu_unknown 162 
#define  ixgbe_phy_fw 161 
#define  ixgbe_phy_generic 160 
#define  ixgbe_phy_nl 159 
#define  ixgbe_phy_qsfp_active_unknown 158 
#define  ixgbe_phy_qsfp_intel 157 
#define  ixgbe_phy_qsfp_passive_unknown 156 
#define  ixgbe_phy_qsfp_unknown 155 
#define  ixgbe_phy_qt 154 
#define  ixgbe_phy_sfp_avago 153 
#define  ixgbe_phy_sfp_ftl 152 
#define  ixgbe_phy_sfp_intel 151 
#define  ixgbe_phy_sfp_passive_tyco 150 
#define  ixgbe_phy_sfp_passive_unknown 149 
#define  ixgbe_phy_sfp_unknown 148 
#define  ixgbe_phy_sfp_unsupported 147 
#define  ixgbe_phy_tn 146 
#define  ixgbe_phy_unknown 145 
#define  ixgbe_phy_x550em_ext_t 144 
#define  ixgbe_phy_xaui 143 
#define  ixgbe_sfp_type_1g_cu_core0 142 
#define  ixgbe_sfp_type_1g_cu_core1 141 
#define  ixgbe_sfp_type_1g_lx_core0 140 
#define  ixgbe_sfp_type_1g_lx_core1 139 
#define  ixgbe_sfp_type_1g_sx_core0 138 
#define  ixgbe_sfp_type_1g_sx_core1 137 
#define  ixgbe_sfp_type_da_cu 136 
#define  ixgbe_sfp_type_da_cu_core0 135 
#define  ixgbe_sfp_type_da_cu_core1 134 
#define  ixgbe_sfp_type_lr 133 
#define  ixgbe_sfp_type_not_present 132 
#define  ixgbe_sfp_type_sr 131 
#define  ixgbe_sfp_type_srlr_core0 130 
#define  ixgbe_sfp_type_srlr_core1 129 
#define  ixgbe_sfp_type_unknown 128 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int*,int*) ; 

__attribute__((used)) static int ixgbe_get_link_ksettings(struct net_device *netdev,
				    struct ethtool_link_ksettings *cmd)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;
	ixgbe_link_speed supported_link;
	bool autoneg = false;
	u32 supported, advertising;

	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);

	hw->mac.ops.get_link_capabilities(hw, &supported_link, &autoneg);

	/* set the supported link speeds */
	if (supported_link & IXGBE_LINK_SPEED_10GB_FULL)
		supported |= ixgbe_get_supported_10gtypes(hw);
	if (supported_link & IXGBE_LINK_SPEED_1GB_FULL)
		supported |= (ixgbe_isbackplane(hw->phy.media_type)) ?
				   SUPPORTED_1000baseKX_Full :
				   SUPPORTED_1000baseT_Full;
	if (supported_link & IXGBE_LINK_SPEED_100_FULL)
		supported |= SUPPORTED_100baseT_Full;
	if (supported_link & IXGBE_LINK_SPEED_10_FULL)
		supported |= SUPPORTED_10baseT_Full;

	/* default advertised speed if phy.autoneg_advertised isn't set */
	advertising = supported;
	/* set the advertised speeds */
	if (hw->phy.autoneg_advertised) {
		advertising = 0;
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_10_FULL)
			advertising |= ADVERTISED_10baseT_Full;
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_100_FULL)
			advertising |= ADVERTISED_100baseT_Full;
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_10GB_FULL)
			advertising |= supported & ADVRTSD_MSK_10G;
		if (hw->phy.autoneg_advertised & IXGBE_LINK_SPEED_1GB_FULL) {
			if (supported & SUPPORTED_1000baseKX_Full)
				advertising |= ADVERTISED_1000baseKX_Full;
			else
				advertising |= ADVERTISED_1000baseT_Full;
		}
	} else {
		if (hw->phy.multispeed_fiber && !autoneg) {
			if (supported_link & IXGBE_LINK_SPEED_10GB_FULL)
				advertising = ADVERTISED_10000baseT_Full;
		}
	}

	if (autoneg) {
		supported |= SUPPORTED_Autoneg;
		advertising |= ADVERTISED_Autoneg;
		cmd->base.autoneg = AUTONEG_ENABLE;
	} else
		cmd->base.autoneg = AUTONEG_DISABLE;

	/* Determine the remaining settings based on the PHY type. */
	switch (adapter->hw.phy.type) {
	case ixgbe_phy_tn:
	case ixgbe_phy_aq:
	case ixgbe_phy_x550em_ext_t:
	case ixgbe_phy_fw:
	case ixgbe_phy_cu_unknown:
		supported |= SUPPORTED_TP;
		advertising |= ADVERTISED_TP;
		cmd->base.port = PORT_TP;
		break;
	case ixgbe_phy_qt:
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		cmd->base.port = PORT_FIBRE;
		break;
	case ixgbe_phy_nl:
	case ixgbe_phy_sfp_passive_tyco:
	case ixgbe_phy_sfp_passive_unknown:
	case ixgbe_phy_sfp_ftl:
	case ixgbe_phy_sfp_avago:
	case ixgbe_phy_sfp_intel:
	case ixgbe_phy_sfp_unknown:
	case ixgbe_phy_qsfp_passive_unknown:
	case ixgbe_phy_qsfp_active_unknown:
	case ixgbe_phy_qsfp_intel:
	case ixgbe_phy_qsfp_unknown:
		/* SFP+ devices, further checking needed */
		switch (adapter->hw.phy.sfp_type) {
		case ixgbe_sfp_type_da_cu:
		case ixgbe_sfp_type_da_cu_core0:
		case ixgbe_sfp_type_da_cu_core1:
			supported |= SUPPORTED_FIBRE;
			advertising |= ADVERTISED_FIBRE;
			cmd->base.port = PORT_DA;
			break;
		case ixgbe_sfp_type_sr:
		case ixgbe_sfp_type_lr:
		case ixgbe_sfp_type_srlr_core0:
		case ixgbe_sfp_type_srlr_core1:
		case ixgbe_sfp_type_1g_sx_core0:
		case ixgbe_sfp_type_1g_sx_core1:
		case ixgbe_sfp_type_1g_lx_core0:
		case ixgbe_sfp_type_1g_lx_core1:
			supported |= SUPPORTED_FIBRE;
			advertising |= ADVERTISED_FIBRE;
			cmd->base.port = PORT_FIBRE;
			break;
		case ixgbe_sfp_type_not_present:
			supported |= SUPPORTED_FIBRE;
			advertising |= ADVERTISED_FIBRE;
			cmd->base.port = PORT_NONE;
			break;
		case ixgbe_sfp_type_1g_cu_core0:
		case ixgbe_sfp_type_1g_cu_core1:
			supported |= SUPPORTED_TP;
			advertising |= ADVERTISED_TP;
			cmd->base.port = PORT_TP;
			break;
		case ixgbe_sfp_type_unknown:
		default:
			supported |= SUPPORTED_FIBRE;
			advertising |= ADVERTISED_FIBRE;
			cmd->base.port = PORT_OTHER;
			break;
		}
		break;
	case ixgbe_phy_xaui:
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		cmd->base.port = PORT_NONE;
		break;
	case ixgbe_phy_unknown:
	case ixgbe_phy_generic:
	case ixgbe_phy_sfp_unsupported:
	default:
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		cmd->base.port = PORT_OTHER;
		break;
	}

	/* Indicate pause support */
	supported |= SUPPORTED_Pause;

	switch (hw->fc.requested_mode) {
	case ixgbe_fc_full:
		advertising |= ADVERTISED_Pause;
		break;
	case ixgbe_fc_rx_pause:
		advertising |= ADVERTISED_Pause |
				     ADVERTISED_Asym_Pause;
		break;
	case ixgbe_fc_tx_pause:
		advertising |= ADVERTISED_Asym_Pause;
		break;
	default:
		advertising &= ~(ADVERTISED_Pause |
				       ADVERTISED_Asym_Pause);
	}

	if (netif_carrier_ok(netdev)) {
		switch (adapter->link_speed) {
		case IXGBE_LINK_SPEED_10GB_FULL:
			cmd->base.speed = SPEED_10000;
			break;
		case IXGBE_LINK_SPEED_5GB_FULL:
			cmd->base.speed = SPEED_5000;
			break;
		case IXGBE_LINK_SPEED_2_5GB_FULL:
			cmd->base.speed = SPEED_2500;
			break;
		case IXGBE_LINK_SPEED_1GB_FULL:
			cmd->base.speed = SPEED_1000;
			break;
		case IXGBE_LINK_SPEED_100_FULL:
			cmd->base.speed = SPEED_100;
			break;
		case IXGBE_LINK_SPEED_10_FULL:
			cmd->base.speed = SPEED_10;
			break;
		default:
			break;
		}
		cmd->base.duplex = DUPLEX_FULL;
	} else {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	}

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}