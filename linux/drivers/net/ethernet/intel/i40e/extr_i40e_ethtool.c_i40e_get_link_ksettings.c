#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_8__ {int requested_mode; } ;
struct i40e_link_status {int link_info; int an_info; } ;
struct TYPE_6__ {int media_type; struct i40e_link_status link_info; } ;
struct i40e_hw {TYPE_4__ fc; TYPE_2__ phy; } ;
struct i40e_pf {struct i40e_hw hw; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct TYPE_7__ {int /*<<< orphan*/  port; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_3__ base; } ;
struct TYPE_5__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  Asym_Pause ; 
 int /*<<< orphan*/  Autoneg ; 
 int /*<<< orphan*/  Backplane ; 
 int /*<<< orphan*/  FIBRE ; 
 int I40E_AQ_AN_COMPLETED ; 
 int I40E_AQ_LINK_UP ; 
#define  I40E_FC_FULL 136 
#define  I40E_FC_RX_PAUSE 135 
#define  I40E_FC_TX_PAUSE 134 
#define  I40E_MEDIA_TYPE_BACKPLANE 133 
#define  I40E_MEDIA_TYPE_BASET 132 
#define  I40E_MEDIA_TYPE_CX4 131 
#define  I40E_MEDIA_TYPE_DA 130 
#define  I40E_MEDIA_TYPE_FIBER 129 
#define  I40E_MEDIA_TYPE_UNKNOWN 128 
 int /*<<< orphan*/  PORT_DA ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_NONE ; 
 int /*<<< orphan*/  PORT_OTHER ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  TP ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_del_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_zero_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_get_settings_link_down (struct i40e_hw*,struct ethtool_link_ksettings*,struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_get_settings_link_up (struct i40e_hw*,struct ethtool_link_ksettings*,struct net_device*,struct i40e_pf*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int i40e_get_link_ksettings(struct net_device *netdev,
				   struct ethtool_link_ksettings *ks)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_hw *hw = &pf->hw;
	struct i40e_link_status *hw_link_info = &hw->phy.link_info;
	bool link_up = hw_link_info->link_info & I40E_AQ_LINK_UP;

	ethtool_link_ksettings_zero_link_mode(ks, supported);
	ethtool_link_ksettings_zero_link_mode(ks, advertising);

	if (link_up)
		i40e_get_settings_link_up(hw, ks, netdev, pf);
	else
		i40e_get_settings_link_down(hw, ks, pf);

	/* Now set the settings that don't rely on link being up/down */
	/* Set autoneg settings */
	ks->base.autoneg = ((hw_link_info->an_info & I40E_AQ_AN_COMPLETED) ?
			    AUTONEG_ENABLE : AUTONEG_DISABLE);

	/* Set media type settings */
	switch (hw->phy.media_type) {
	case I40E_MEDIA_TYPE_BACKPLANE:
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, supported, Backplane);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Backplane);
		ks->base.port = PORT_NONE;
		break;
	case I40E_MEDIA_TYPE_BASET:
		ethtool_link_ksettings_add_link_mode(ks, supported, TP);
		ethtool_link_ksettings_add_link_mode(ks, advertising, TP);
		ks->base.port = PORT_TP;
		break;
	case I40E_MEDIA_TYPE_DA:
	case I40E_MEDIA_TYPE_CX4:
		ethtool_link_ksettings_add_link_mode(ks, supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(ks, advertising, FIBRE);
		ks->base.port = PORT_DA;
		break;
	case I40E_MEDIA_TYPE_FIBER:
		ethtool_link_ksettings_add_link_mode(ks, supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(ks, advertising, FIBRE);
		ks->base.port = PORT_FIBRE;
		break;
	case I40E_MEDIA_TYPE_UNKNOWN:
	default:
		ks->base.port = PORT_OTHER;
		break;
	}

	/* Set flow control settings */
	ethtool_link_ksettings_add_link_mode(ks, supported, Pause);

	switch (hw->fc.requested_mode) {
	case I40E_FC_FULL:
		ethtool_link_ksettings_add_link_mode(ks, advertising, Pause);
		break;
	case I40E_FC_TX_PAUSE:
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Asym_Pause);
		break;
	case I40E_FC_RX_PAUSE:
		ethtool_link_ksettings_add_link_mode(ks, advertising, Pause);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Asym_Pause);
		break;
	default:
		ethtool_link_ksettings_del_link_mode(ks, advertising, Pause);
		ethtool_link_ksettings_del_link_mode(ks, advertising,
						     Asym_Pause);
		break;
	}

	return 0;
}