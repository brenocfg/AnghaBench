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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_11__ {scalar_t__ mdix; int /*<<< orphan*/  autoneg_advertised; } ;
struct TYPE_9__ {int /*<<< orphan*/  requested_mode; } ;
struct TYPE_8__ {int autoneg; } ;
struct igc_hw {TYPE_5__ phy; TYPE_3__ fc; TYPE_2__ mac; } ;
struct igc_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; TYPE_4__* pdev; scalar_t__ fc_autoneg; struct igc_hw hw; } ;
struct TYPE_12__ {scalar_t__ eth_tp_mdix_ctrl; scalar_t__ autoneg; } ;
struct TYPE_7__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_6__ base; TYPE_1__ link_modes; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ AUTO_ALL_MODES ; 
 int EINVAL ; 
 scalar_t__ ETH_TP_MDI_AUTO ; 
 int /*<<< orphan*/  __IGC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ igc_check_reset_block (struct igc_hw*) ; 
 int /*<<< orphan*/  igc_down (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_fc_default ; 
 int /*<<< orphan*/  igc_reset (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_up (struct igc_adapter*) ; 
 struct igc_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int igc_set_link_ksettings(struct net_device *netdev,
				  const struct ethtool_link_ksettings *cmd)
{
	struct igc_adapter *adapter = netdev_priv(netdev);
	struct igc_hw *hw = &adapter->hw;
	u32 advertising;

	/* When adapter in resetting mode, autoneg/speed/duplex
	 * cannot be changed
	 */
	if (igc_check_reset_block(hw)) {
		dev_err(&adapter->pdev->dev,
			"Cannot change link characteristics when reset is active.\n");
		return -EINVAL;
	}

	/* MDI setting is only allowed when autoneg enabled because
	 * some hardware doesn't allow MDI setting when speed or
	 * duplex is forced.
	 */
	if (cmd->base.eth_tp_mdix_ctrl) {
		if (cmd->base.eth_tp_mdix_ctrl != ETH_TP_MDI_AUTO &&
		    cmd->base.autoneg != AUTONEG_ENABLE) {
			dev_err(&adapter->pdev->dev, "forcing MDI/MDI-X state is not supported when link speed and/or duplex are forced\n");
			return -EINVAL;
		}
	}

	while (test_and_set_bit(__IGC_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		hw->mac.autoneg = 1;
		hw->phy.autoneg_advertised = advertising;
		if (adapter->fc_autoneg)
			hw->fc.requested_mode = igc_fc_default;
	} else {
		/* calling this overrides forced MDI setting */
		dev_info(&adapter->pdev->dev,
			 "Force mode currently not supported\n");
	}

	/* MDI-X => 2; MDI => 1; Auto => 3 */
	if (cmd->base.eth_tp_mdix_ctrl) {
		/* fix up the value for auto (3 => 0) as zero is mapped
		 * internally to auto
		 */
		if (cmd->base.eth_tp_mdix_ctrl == ETH_TP_MDI_AUTO)
			hw->phy.mdix = AUTO_ALL_MODES;
		else
			hw->phy.mdix = cmd->base.eth_tp_mdix_ctrl;
	}

	/* reset the link */
	if (netif_running(adapter->netdev)) {
		igc_down(adapter);
		igc_up(adapter);
	} else {
		igc_reset(adapter);
	}

	clear_bit(__IGC_RESETTING, &adapter->state);

	return 0;
}