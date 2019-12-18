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
typedef  scalar_t__ u64 ;
struct net_device {int dummy; } ;
struct gve_tx_ring {scalar_t__ stop_queue; scalar_t__ wake_queue; scalar_t__ done; scalar_t__ req; scalar_t__ bytes_done; scalar_t__ pkt_done; int /*<<< orphan*/  statss; } ;
struct gve_rx_ring {scalar_t__ fill_cnt; scalar_t__ cnt; scalar_t__ rbytes; scalar_t__ rpackets; int /*<<< orphan*/  statss; } ;
struct TYPE_4__ {int num_queues; } ;
struct TYPE_3__ {int num_queues; } ;
struct gve_priv {TYPE_2__ tx_cfg; struct gve_tx_ring* tx; TYPE_1__ rx_cfg; struct gve_rx_ring* rx; scalar_t__ tx_timeo_cnt; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int GVE_MAIN_STATS_LEN ; 
 int NUM_GVE_RX_CNTS ; 
 int NUM_GVE_TX_CNTS ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gve_tx_load_event_counter (struct gve_priv*,struct gve_tx_ring*) ; 
 struct gve_priv* netdev_priv (struct net_device*) ; 
 unsigned int u64_stats_fetch_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
gve_get_ethtool_stats(struct net_device *netdev,
		      struct ethtool_stats *stats, u64 *data)
{
	struct gve_priv *priv = netdev_priv(netdev);
	u64 rx_pkts, rx_bytes, tx_pkts, tx_bytes;
	unsigned int start;
	int ring;
	int i;

	ASSERT_RTNL();

	for (rx_pkts = 0, rx_bytes = 0, ring = 0;
	     ring < priv->rx_cfg.num_queues; ring++) {
		if (priv->rx) {
			do {
				start =
				  u64_stats_fetch_begin(&priv->rx[ring].statss);
				rx_pkts += priv->rx[ring].rpackets;
				rx_bytes += priv->rx[ring].rbytes;
			} while (u64_stats_fetch_retry(&priv->rx[ring].statss,
						       start));
		}
	}
	for (tx_pkts = 0, tx_bytes = 0, ring = 0;
	     ring < priv->tx_cfg.num_queues; ring++) {
		if (priv->tx) {
			do {
				start =
				  u64_stats_fetch_begin(&priv->tx[ring].statss);
				tx_pkts += priv->tx[ring].pkt_done;
				tx_bytes += priv->tx[ring].bytes_done;
			} while (u64_stats_fetch_retry(&priv->tx[ring].statss,
						       start));
		}
	}

	i = 0;
	data[i++] = rx_pkts;
	data[i++] = tx_pkts;
	data[i++] = rx_bytes;
	data[i++] = tx_bytes;
	/* Skip rx_dropped and tx_dropped */
	i += 2;
	data[i++] = priv->tx_timeo_cnt;
	i = GVE_MAIN_STATS_LEN;

	/* walk RX rings */
	if (priv->rx) {
		for (ring = 0; ring < priv->rx_cfg.num_queues; ring++) {
			struct gve_rx_ring *rx = &priv->rx[ring];

			data[i++] = rx->cnt;
			data[i++] = rx->fill_cnt;
		}
	} else {
		i += priv->rx_cfg.num_queues * NUM_GVE_RX_CNTS;
	}
	/* walk TX rings */
	if (priv->tx) {
		for (ring = 0; ring < priv->tx_cfg.num_queues; ring++) {
			struct gve_tx_ring *tx = &priv->tx[ring];

			data[i++] = tx->req;
			data[i++] = tx->done;
			data[i++] = tx->wake_queue;
			data[i++] = tx->stop_queue;
			data[i++] = be32_to_cpu(gve_tx_load_event_counter(priv,
									  tx));
		}
	} else {
		i += priv->tx_cfg.num_queues * NUM_GVE_TX_CNTS;
	}
}