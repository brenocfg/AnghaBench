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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; } ;
struct nicvf_hw_stats {int /*<<< orphan*/  tx_drops; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_mcast_frames; int /*<<< orphan*/  rx_drops; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_bytes; } ;
struct nicvf {struct nicvf_hw_stats hw_stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nicvf_update_stats (struct nicvf*) ; 

__attribute__((used)) static void nicvf_get_stats64(struct net_device *netdev,
			      struct rtnl_link_stats64 *stats)
{
	struct nicvf *nic = netdev_priv(netdev);
	struct nicvf_hw_stats *hw_stats = &nic->hw_stats;

	nicvf_update_stats(nic);

	stats->rx_bytes = hw_stats->rx_bytes;
	stats->rx_packets = hw_stats->rx_frames;
	stats->rx_dropped = hw_stats->rx_drops;
	stats->multicast = hw_stats->rx_mcast_frames;

	stats->tx_bytes = hw_stats->tx_bytes;
	stats->tx_packets = hw_stats->tx_frames;
	stats->tx_dropped = hw_stats->tx_drops;

}