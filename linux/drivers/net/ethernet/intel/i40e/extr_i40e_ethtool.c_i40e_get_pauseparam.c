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
struct TYPE_8__ {scalar_t__ current_mode; } ;
struct TYPE_7__ {scalar_t__ pfcenable; } ;
struct i40e_dcbx_config {TYPE_3__ pfc; } ;
struct i40e_link_status {int an_info; } ;
struct TYPE_6__ {struct i40e_link_status link_info; } ;
struct i40e_hw {TYPE_4__ fc; struct i40e_dcbx_config local_dcbx_config; TYPE_2__ phy; } ;
struct i40e_pf {struct i40e_hw hw; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; int /*<<< orphan*/  autoneg; } ;
struct TYPE_5__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int I40E_AQ_AN_COMPLETED ; 
 scalar_t__ I40E_FC_FULL ; 
 scalar_t__ I40E_FC_RX_PAUSE ; 
 scalar_t__ I40E_FC_TX_PAUSE ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void i40e_get_pauseparam(struct net_device *netdev,
				struct ethtool_pauseparam *pause)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_hw *hw = &pf->hw;
	struct i40e_link_status *hw_link_info = &hw->phy.link_info;
	struct i40e_dcbx_config *dcbx_cfg = &hw->local_dcbx_config;

	pause->autoneg =
		((hw_link_info->an_info & I40E_AQ_AN_COMPLETED) ?
		  AUTONEG_ENABLE : AUTONEG_DISABLE);

	/* PFC enabled so report LFC as off */
	if (dcbx_cfg->pfc.pfcenable) {
		pause->rx_pause = 0;
		pause->tx_pause = 0;
		return;
	}

	if (hw->fc.current_mode == I40E_FC_RX_PAUSE) {
		pause->rx_pause = 1;
	} else if (hw->fc.current_mode == I40E_FC_TX_PAUSE) {
		pause->tx_pause = 1;
	} else if (hw->fc.current_mode == I40E_FC_FULL) {
		pause->rx_pause = 1;
		pause->tx_pause = 1;
	}
}