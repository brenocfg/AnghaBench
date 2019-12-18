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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  rx_desc_unk_state; int /*<<< orphan*/  tx_iommu_map_error; int /*<<< orphan*/  rx_iommu_map_error; int /*<<< orphan*/  alloc_rx_skb_error; int /*<<< orphan*/  tx_timeouts; int /*<<< orphan*/  rx_desc_error; } ;
struct spider_net_card {TYPE_2__ spider_stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 struct spider_net_card* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void spider_net_get_ethtool_stats(struct net_device *netdev,
		struct ethtool_stats *stats, u64 *data)
{
	struct spider_net_card *card = netdev_priv(netdev);

	data[0] = netdev->stats.tx_packets;
	data[1] = netdev->stats.tx_bytes;
	data[2] = netdev->stats.rx_packets;
	data[3] = netdev->stats.rx_bytes;
	data[4] = netdev->stats.tx_errors;
	data[5] = netdev->stats.tx_dropped;
	data[6] = netdev->stats.rx_dropped;
	data[7] = card->spider_stats.rx_desc_error;
	data[8] = card->spider_stats.tx_timeouts;
	data[9] = card->spider_stats.alloc_rx_skb_error;
	data[10] = card->spider_stats.rx_iommu_map_error;
	data[11] = card->spider_stats.tx_iommu_map_error;
	data[12] = card->spider_stats.rx_desc_unk_state;
}