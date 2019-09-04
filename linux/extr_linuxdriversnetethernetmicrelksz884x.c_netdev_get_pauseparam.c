#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct ksz_hw {int overrides; int rx_cfg; int tx_cfg; int /*<<< orphan*/  ksz_switch; } ;
struct ethtool_pauseparam {int autoneg; int rx_pause; int tx_pause; } ;
struct dev_priv {struct dev_info* adapter; } ;
struct dev_info {struct ksz_hw hw; } ;

/* Variables and functions */
 int DMA_RX_FLOW_ENABLE ; 
 int DMA_TX_FLOW_ENABLE ; 
 int /*<<< orphan*/  KS8842_SWITCH_CTRL_1_OFFSET ; 
 int PAUSE_FLOW_CTRL ; 
 int /*<<< orphan*/  SWITCH_RX_FLOW_CTRL ; 
 int /*<<< orphan*/  SWITCH_TX_FLOW_CTRL ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ sw_chk (struct ksz_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netdev_get_pauseparam(struct net_device *dev,
	struct ethtool_pauseparam *pause)
{
	struct dev_priv *priv = netdev_priv(dev);
	struct dev_info *hw_priv = priv->adapter;
	struct ksz_hw *hw = &hw_priv->hw;

	pause->autoneg = (hw->overrides & PAUSE_FLOW_CTRL) ? 0 : 1;
	if (!hw->ksz_switch) {
		pause->rx_pause =
			(hw->rx_cfg & DMA_RX_FLOW_ENABLE) ? 1 : 0;
		pause->tx_pause =
			(hw->tx_cfg & DMA_TX_FLOW_ENABLE) ? 1 : 0;
	} else {
		pause->rx_pause =
			(sw_chk(hw, KS8842_SWITCH_CTRL_1_OFFSET,
				SWITCH_RX_FLOW_CTRL)) ? 1 : 0;
		pause->tx_pause =
			(sw_chk(hw, KS8842_SWITCH_CTRL_1_OFFSET,
				SWITCH_TX_FLOW_CTRL)) ? 1 : 0;
	}
}