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
 int TIM_START ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int* rxirqmask ; 
 int skge_clk2usec (struct skge_hw*,int) ; 
 int skge_read32 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int* txirqmask ; 

__attribute__((used)) static int skge_get_coalesce(struct net_device *dev,
			     struct ethtool_coalesce *ecmd)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	int port = skge->port;

	ecmd->rx_coalesce_usecs = 0;
	ecmd->tx_coalesce_usecs = 0;

	if (skge_read32(hw, B2_IRQM_CTRL) & TIM_START) {
		u32 delay = skge_clk2usec(hw, skge_read32(hw, B2_IRQM_INI));
		u32 msk = skge_read32(hw, B2_IRQM_MSK);

		if (msk & rxirqmask[port])
			ecmd->rx_coalesce_usecs = delay;
		if (msk & txirqmask[port])
			ecmd->tx_coalesce_usecs = delay;
	}

	return 0;
}