#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  txdropped; int /*<<< orphan*/  rxdropped; int /*<<< orphan*/  txbytes; scalar_t__ lrobytes; scalar_t__ rxbytes; int /*<<< orphan*/  xmitfinished; scalar_t__ lro_pkts; scalar_t__ rx_pkts; } ;
struct qlcnic_adapter {TYPE_1__ stats; int /*<<< orphan*/  state; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_bytes; scalar_t__ rx_bytes; int /*<<< orphan*/  tx_packets; scalar_t__ rx_packets; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_update_stats (struct qlcnic_adapter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device_stats *qlcnic_get_stats(struct net_device *netdev)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct net_device_stats *stats = &netdev->stats;

	if (test_bit(__QLCNIC_DEV_UP, &adapter->state))
		qlcnic_update_stats(adapter);

	stats->rx_packets = adapter->stats.rx_pkts + adapter->stats.lro_pkts;
	stats->tx_packets = adapter->stats.xmitfinished;
	stats->rx_bytes = adapter->stats.rxbytes + adapter->stats.lrobytes;
	stats->tx_bytes = adapter->stats.txbytes;
	stats->rx_dropped = adapter->stats.rxdropped;
	stats->tx_dropped = adapter->stats.txdropped;

	return stats;
}