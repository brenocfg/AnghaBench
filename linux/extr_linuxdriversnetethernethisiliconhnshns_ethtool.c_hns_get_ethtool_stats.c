#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_compressed; int /*<<< orphan*/  rx_compressed; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_6__ {int /*<<< orphan*/  counter; } ;
struct TYPE_5__ {int /*<<< orphan*/  counter; } ;
struct net_device {TYPE_2__ tx_dropped; TYPE_1__ rx_dropped; int /*<<< orphan*/  stats; } ;
struct hns_nic_priv {int /*<<< orphan*/  tx_timeout_count; struct hnae_handle* ae_handle; } ;
struct hnae_handle {TYPE_4__* dev; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_8__ {TYPE_3__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_stats ) (struct hnae_handle*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* update_stats ) (struct hnae_handle*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 struct rtnl_link_stats64* dev_get_stats (struct net_device*,struct rtnl_link_stats64*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct hnae_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct hnae_handle*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_get_ethtool_stats(struct net_device *netdev,
				  struct ethtool_stats *stats, u64 *data)
{
	u64 *p = data;
	struct hns_nic_priv *priv = netdev_priv(netdev);
	struct hnae_handle *h = priv->ae_handle;
	const struct rtnl_link_stats64 *net_stats;
	struct rtnl_link_stats64 temp;

	if (!h->dev->ops->get_stats || !h->dev->ops->update_stats) {
		netdev_err(netdev, "get_stats or update_stats is null!\n");
		return;
	}

	h->dev->ops->update_stats(h, &netdev->stats);

	net_stats = dev_get_stats(netdev, &temp);

	/* get netdev statistics */
	p[0] = net_stats->rx_packets;
	p[1] = net_stats->tx_packets;
	p[2] = net_stats->rx_bytes;
	p[3] = net_stats->tx_bytes;
	p[4] = net_stats->rx_errors;
	p[5] = net_stats->tx_errors;
	p[6] = net_stats->rx_dropped;
	p[7] = net_stats->tx_dropped;
	p[8] = net_stats->multicast;
	p[9] = net_stats->collisions;
	p[10] = net_stats->rx_over_errors;
	p[11] = net_stats->rx_crc_errors;
	p[12] = net_stats->rx_frame_errors;
	p[13] = net_stats->rx_fifo_errors;
	p[14] = net_stats->rx_missed_errors;
	p[15] = net_stats->tx_aborted_errors;
	p[16] = net_stats->tx_carrier_errors;
	p[17] = net_stats->tx_fifo_errors;
	p[18] = net_stats->tx_heartbeat_errors;
	p[19] = net_stats->rx_length_errors;
	p[20] = net_stats->tx_window_errors;
	p[21] = net_stats->rx_compressed;
	p[22] = net_stats->tx_compressed;

	p[23] = netdev->rx_dropped.counter;
	p[24] = netdev->tx_dropped.counter;

	p[25] = priv->tx_timeout_count;

	/* get driver statistics */
	h->dev->ops->get_stats(h, &p[26]);
}