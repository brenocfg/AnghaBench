#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_compressed; int /*<<< orphan*/  rx_compressed; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  collisions; void* tx_dropped; void* rx_dropped; void* tx_errors; int /*<<< orphan*/  rx_missed_errors; void* rx_crc_errors; void* rx_length_errors; void* multicast; void* rx_errors; void* rx_packets; void* rx_bytes; void* tx_packets; void* tx_bytes; } ;
struct TYPE_12__ {int /*<<< orphan*/  tx_compressed; int /*<<< orphan*/  rx_compressed; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  rx_missed_errors; } ;
struct net_device {TYPE_6__ stats; } ;
struct hns3_nic_priv {TYPE_4__* ring_data; int /*<<< orphan*/  state; struct hnae3_handle* ae_handle; } ;
struct TYPE_11__ {scalar_t__ err_pkt_len; scalar_t__ rx_multicast; scalar_t__ l2_err; scalar_t__ l3l4_csum_err; scalar_t__ rx_pkts; scalar_t__ rx_bytes; scalar_t__ tx_tso_err; scalar_t__ tx_l2l3l4_err; scalar_t__ tx_l4_proto_err; scalar_t__ tx_vlan_err; scalar_t__ sw_err_cnt; scalar_t__ tx_pkts; scalar_t__ tx_bytes; } ;
struct hns3_enet_ring {TYPE_5__ stats; int /*<<< orphan*/  syncp; } ;
struct TYPE_7__ {int num_tqps; } ;
struct hnae3_handle {TYPE_3__* ae_algo; TYPE_1__ kinfo; } ;
struct TYPE_10__ {struct hns3_enet_ring* ring; } ;
struct TYPE_9__ {TYPE_2__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* update_stats ) (struct hnae3_handle*,TYPE_6__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_NIC_STATE_DOWN ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,TYPE_6__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void hns3_nic_get_stats64(struct net_device *netdev,
				 struct rtnl_link_stats64 *stats)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	int queue_num = priv->ae_handle->kinfo.num_tqps;
	struct hnae3_handle *handle = priv->ae_handle;
	struct hns3_enet_ring *ring;
	u64 rx_length_errors = 0;
	u64 rx_crc_errors = 0;
	u64 rx_multicast = 0;
	unsigned int start;
	u64 tx_errors = 0;
	u64 rx_errors = 0;
	unsigned int idx;
	u64 tx_bytes = 0;
	u64 rx_bytes = 0;
	u64 tx_pkts = 0;
	u64 rx_pkts = 0;
	u64 tx_drop = 0;
	u64 rx_drop = 0;

	if (test_bit(HNS3_NIC_STATE_DOWN, &priv->state))
		return;

	handle->ae_algo->ops->update_stats(handle, &netdev->stats);

	for (idx = 0; idx < queue_num; idx++) {
		/* fetch the tx stats */
		ring = priv->ring_data[idx].ring;
		do {
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			tx_bytes += ring->stats.tx_bytes;
			tx_pkts += ring->stats.tx_pkts;
			tx_drop += ring->stats.sw_err_cnt;
			tx_drop += ring->stats.tx_vlan_err;
			tx_drop += ring->stats.tx_l4_proto_err;
			tx_drop += ring->stats.tx_l2l3l4_err;
			tx_drop += ring->stats.tx_tso_err;
			tx_errors += ring->stats.sw_err_cnt;
			tx_errors += ring->stats.tx_vlan_err;
			tx_errors += ring->stats.tx_l4_proto_err;
			tx_errors += ring->stats.tx_l2l3l4_err;
			tx_errors += ring->stats.tx_tso_err;
		} while (u64_stats_fetch_retry_irq(&ring->syncp, start));

		/* fetch the rx stats */
		ring = priv->ring_data[idx + queue_num].ring;
		do {
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			rx_bytes += ring->stats.rx_bytes;
			rx_pkts += ring->stats.rx_pkts;
			rx_drop += ring->stats.l2_err;
			rx_errors += ring->stats.l2_err;
			rx_errors += ring->stats.l3l4_csum_err;
			rx_crc_errors += ring->stats.l2_err;
			rx_multicast += ring->stats.rx_multicast;
			rx_length_errors += ring->stats.err_pkt_len;
		} while (u64_stats_fetch_retry_irq(&ring->syncp, start));
	}

	stats->tx_bytes = tx_bytes;
	stats->tx_packets = tx_pkts;
	stats->rx_bytes = rx_bytes;
	stats->rx_packets = rx_pkts;

	stats->rx_errors = rx_errors;
	stats->multicast = rx_multicast;
	stats->rx_length_errors = rx_length_errors;
	stats->rx_crc_errors = rx_crc_errors;
	stats->rx_missed_errors = netdev->stats.rx_missed_errors;

	stats->tx_errors = tx_errors;
	stats->rx_dropped = rx_drop;
	stats->tx_dropped = tx_drop;
	stats->collisions = netdev->stats.collisions;
	stats->rx_over_errors = netdev->stats.rx_over_errors;
	stats->rx_frame_errors = netdev->stats.rx_frame_errors;
	stats->rx_fifo_errors = netdev->stats.rx_fifo_errors;
	stats->tx_aborted_errors = netdev->stats.tx_aborted_errors;
	stats->tx_carrier_errors = netdev->stats.tx_carrier_errors;
	stats->tx_fifo_errors = netdev->stats.tx_fifo_errors;
	stats->tx_heartbeat_errors = netdev->stats.tx_heartbeat_errors;
	stats->tx_window_errors = netdev->stats.tx_window_errors;
	stats->rx_compressed = netdev->stats.rx_compressed;
	stats->tx_compressed = netdev->stats.tx_compressed;
}