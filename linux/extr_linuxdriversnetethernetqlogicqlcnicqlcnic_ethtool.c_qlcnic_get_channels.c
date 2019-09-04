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
struct qlcnic_adapter {int /*<<< orphan*/  drv_tx_rings; int /*<<< orphan*/  drv_sds_rings; int /*<<< orphan*/  max_tx_rings; int /*<<< orphan*/  max_sds_rings; } ;
struct net_device {int dummy; } ;
struct ethtool_channels {int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  max_rx; } ;

/* Variables and functions */
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void qlcnic_get_channels(struct net_device *dev,
		struct ethtool_channels *channel)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);

	channel->max_rx = adapter->max_sds_rings;
	channel->max_tx = adapter->max_tx_rings;
	channel->rx_count = adapter->drv_sds_rings;
	channel->tx_count = adapter->drv_tx_rings;
}