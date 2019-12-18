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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; } ;
struct net_device {int dummy; } ;
struct hinic_txq_stats {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  pkts; int /*<<< orphan*/  bytes; } ;
struct hinic_rxq_stats {int /*<<< orphan*/  errors; int /*<<< orphan*/  pkts; int /*<<< orphan*/  bytes; } ;
struct hinic_dev {int flags; int /*<<< orphan*/  mgmt_lock; struct hinic_txq_stats tx_stats; struct hinic_rxq_stats rx_stats; } ;

/* Variables and functions */
 int HINIC_INTF_UP ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_nic_stats (struct hinic_dev*) ; 

__attribute__((used)) static void hinic_get_stats64(struct net_device *netdev,
			      struct rtnl_link_stats64 *stats)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	struct hinic_rxq_stats *nic_rx_stats;
	struct hinic_txq_stats *nic_tx_stats;

	nic_rx_stats = &nic_dev->rx_stats;
	nic_tx_stats = &nic_dev->tx_stats;

	down(&nic_dev->mgmt_lock);

	if (nic_dev->flags & HINIC_INTF_UP)
		update_nic_stats(nic_dev);

	up(&nic_dev->mgmt_lock);

	stats->rx_bytes   = nic_rx_stats->bytes;
	stats->rx_packets = nic_rx_stats->pkts;
	stats->rx_errors  = nic_rx_stats->errors;

	stats->tx_bytes   = nic_tx_stats->bytes;
	stats->tx_packets = nic_tx_stats->pkts;
	stats->tx_errors  = nic_tx_stats->tx_dropped;
}