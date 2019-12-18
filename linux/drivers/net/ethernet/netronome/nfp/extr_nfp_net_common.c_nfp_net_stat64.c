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
typedef  scalar_t__ u64 ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  multicast; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct nfp_net_r_vector {scalar_t__ tx_errors; scalar_t__ tx_bytes; scalar_t__ tx_pkts; int /*<<< orphan*/  tx_sync; scalar_t__ rx_drops; scalar_t__ rx_bytes; scalar_t__ rx_pkts; int /*<<< orphan*/  rx_sync; } ;
struct nfp_net {int max_r_vecs; struct nfp_net_r_vector* r_vecs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_NET_CFG_STATS_RX_DISCARDS ; 
 int /*<<< orphan*/  NFP_NET_CFG_STATS_RX_ERRORS ; 
 int /*<<< orphan*/  NFP_NET_CFG_STATS_RX_MC_FRAMES ; 
 int /*<<< orphan*/  NFP_NET_CFG_STATS_TX_DISCARDS ; 
 int /*<<< orphan*/  NFP_NET_CFG_STATS_TX_ERRORS ; 
 struct nfp_net* netdev_priv (struct net_device*) ; 
 scalar_t__ nn_readq (struct nfp_net*,int /*<<< orphan*/ ) ; 
 unsigned int u64_stats_fetch_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void nfp_net_stat64(struct net_device *netdev,
			   struct rtnl_link_stats64 *stats)
{
	struct nfp_net *nn = netdev_priv(netdev);
	int r;

	/* Collect software stats */
	for (r = 0; r < nn->max_r_vecs; r++) {
		struct nfp_net_r_vector *r_vec = &nn->r_vecs[r];
		u64 data[3];
		unsigned int start;

		do {
			start = u64_stats_fetch_begin(&r_vec->rx_sync);
			data[0] = r_vec->rx_pkts;
			data[1] = r_vec->rx_bytes;
			data[2] = r_vec->rx_drops;
		} while (u64_stats_fetch_retry(&r_vec->rx_sync, start));
		stats->rx_packets += data[0];
		stats->rx_bytes += data[1];
		stats->rx_dropped += data[2];

		do {
			start = u64_stats_fetch_begin(&r_vec->tx_sync);
			data[0] = r_vec->tx_pkts;
			data[1] = r_vec->tx_bytes;
			data[2] = r_vec->tx_errors;
		} while (u64_stats_fetch_retry(&r_vec->tx_sync, start));
		stats->tx_packets += data[0];
		stats->tx_bytes += data[1];
		stats->tx_errors += data[2];
	}

	/* Add in device stats */
	stats->multicast += nn_readq(nn, NFP_NET_CFG_STATS_RX_MC_FRAMES);
	stats->rx_dropped += nn_readq(nn, NFP_NET_CFG_STATS_RX_DISCARDS);
	stats->rx_errors += nn_readq(nn, NFP_NET_CFG_STATS_RX_ERRORS);

	stats->tx_dropped += nn_readq(nn, NFP_NET_CFG_STATS_TX_DISCARDS);
	stats->tx_errors += nn_readq(nn, NFP_NET_CFG_STATS_TX_ERRORS);
}