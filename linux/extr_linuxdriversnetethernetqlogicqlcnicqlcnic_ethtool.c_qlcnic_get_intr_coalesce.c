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
struct qlcnic_adapter {scalar_t__ is_up; TYPE_2__* ahw; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_time_us; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_time_us; } ;
struct TYPE_4__ {TYPE_1__ coal; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ QLCNIC_ADAPTER_UP_MAGIC ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int qlcnic_get_intr_coalesce(struct net_device *netdev,
			struct ethtool_coalesce *ethcoal)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);

	if (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		return -EINVAL;

	ethcoal->rx_coalesce_usecs = adapter->ahw->coal.rx_time_us;
	ethcoal->rx_max_coalesced_frames = adapter->ahw->coal.rx_packets;
	ethcoal->tx_coalesce_usecs = adapter->ahw->coal.tx_time_us;
	ethcoal->tx_max_coalesced_frames = adapter->ahw->coal.tx_packets;

	return 0;
}