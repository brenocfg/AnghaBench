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
struct qlcnic_adapter {int /*<<< orphan*/  state; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; int rx_max_coalesced_frames; int tx_coalesce_usecs; int tx_max_coalesced_frames; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ tx_coalesce_usecs_high; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_coalesce_usecs_high; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_low; scalar_t__ rx_max_coalesced_frames_low; scalar_t__ rx_coalesce_usecs_low; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int qlcnic_config_intr_coalesce (struct qlcnic_adapter*,struct ethtool_coalesce*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_set_intr_coalesce(struct net_device *netdev,
			struct ethtool_coalesce *ethcoal)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	int err;

	if (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		return -EINVAL;

	/*
	* Return Error if unsupported values or
	* unsupported parameters are set.
	*/
	if (ethcoal->rx_coalesce_usecs > 0xffff ||
	    ethcoal->rx_max_coalesced_frames > 0xffff ||
	    ethcoal->tx_coalesce_usecs > 0xffff ||
	    ethcoal->tx_max_coalesced_frames > 0xffff ||
	    ethcoal->rx_coalesce_usecs_irq ||
	    ethcoal->rx_max_coalesced_frames_irq ||
	    ethcoal->tx_coalesce_usecs_irq ||
	    ethcoal->tx_max_coalesced_frames_irq ||
	    ethcoal->stats_block_coalesce_usecs ||
	    ethcoal->use_adaptive_rx_coalesce ||
	    ethcoal->use_adaptive_tx_coalesce ||
	    ethcoal->pkt_rate_low ||
	    ethcoal->rx_coalesce_usecs_low ||
	    ethcoal->rx_max_coalesced_frames_low ||
	    ethcoal->tx_coalesce_usecs_low ||
	    ethcoal->tx_max_coalesced_frames_low ||
	    ethcoal->pkt_rate_high ||
	    ethcoal->rx_coalesce_usecs_high ||
	    ethcoal->rx_max_coalesced_frames_high ||
	    ethcoal->tx_coalesce_usecs_high ||
	    ethcoal->tx_max_coalesced_frames_high)
		return -EINVAL;

	err = qlcnic_config_intr_coalesce(adapter, ethcoal);

	return err;
}