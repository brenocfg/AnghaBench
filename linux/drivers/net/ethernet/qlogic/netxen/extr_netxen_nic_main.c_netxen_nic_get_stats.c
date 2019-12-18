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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; scalar_t__ rx_packets; } ;
struct TYPE_2__ {int /*<<< orphan*/  txdropped; int /*<<< orphan*/  rxdropped; int /*<<< orphan*/  txbytes; int /*<<< orphan*/  rxbytes; int /*<<< orphan*/  xmitfinished; scalar_t__ lro_pkts; scalar_t__ rx_pkts; } ;
struct netxen_adapter {TYPE_1__ stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct netxen_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void netxen_nic_get_stats(struct net_device *netdev,
				 struct rtnl_link_stats64 *stats)
{
	struct netxen_adapter *adapter = netdev_priv(netdev);

	stats->rx_packets = adapter->stats.rx_pkts + adapter->stats.lro_pkts;
	stats->tx_packets = adapter->stats.xmitfinished;
	stats->rx_bytes = adapter->stats.rxbytes;
	stats->tx_bytes = adapter->stats.txbytes;
	stats->rx_dropped = adapter->stats.rxdropped;
	stats->tx_dropped = adapter->stats.txdropped;
}