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
typedef  int u32 ;
struct skge_port {int port; struct skge_hw* hw; } ;
struct skge_hw {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; int tx_coalesce_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2_IRQM_CTRL ; 
 int /*<<< orphan*/  B2_IRQM_INI ; 
 int /*<<< orphan*/  B2_IRQM_MSK ; 
 int EINVAL ; 
 int TIM_START ; 
 int TIM_STOP ; 
 int min (int,int) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int* rxirqmask ; 
 int skge_read32 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int skge_usecs2clk (struct skge_hw*,int) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int* txirqmask ; 

__attribute__((used)) static int skge_set_coalesce(struct net_device *dev,
			     struct ethtool_coalesce *ecmd)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	u32 msk = skge_read32(hw, B2_IRQM_MSK);
	u32 delay = 25;

	if (ecmd->rx_coalesce_usecs == 0)
		msk &= ~rxirqmask[port];
	else if (ecmd->rx_coalesce_usecs < 25 ||
		 ecmd->rx_coalesce_usecs > 33333)
		return -EINVAL;
	else {
		msk |= rxirqmask[port];
		delay = ecmd->rx_coalesce_usecs;
	}

	if (ecmd->tx_coalesce_usecs == 0)
		msk &= ~txirqmask[port];
	else if (ecmd->tx_coalesce_usecs < 25 ||
		 ecmd->tx_coalesce_usecs > 33333)
		return -EINVAL;
	else {
		msk |= txirqmask[port];
		delay = min(delay, ecmd->rx_coalesce_usecs);
	}

	skge_write32(hw, B2_IRQM_MSK, msk);
	if (msk == 0)
		skge_write32(hw, B2_IRQM_CTRL, TIM_STOP);
	else {
		skge_write32(hw, B2_IRQM_INI, skge_usecs2clk(hw, delay));
		skge_write32(hw, B2_IRQM_CTRL, TIM_START);
	}
	return 0;
}