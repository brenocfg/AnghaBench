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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct nfp_net_r_vector {scalar_t__ tx_errors; scalar_t__ tx_bytes; scalar_t__ tx_pkts; int /*<<< orphan*/  tx_sync; scalar_t__ rx_drops; scalar_t__ rx_bytes; scalar_t__ rx_pkts; int /*<<< orphan*/  rx_sync; } ;
struct nfp_net {int max_r_vecs; struct nfp_net_r_vector* r_vecs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct nfp_net* netdev_priv (struct net_device*) ; 
 unsigned int u64_stats_fetch_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void nfp_net_stat64(struct net_device *netdev,
			   struct rtnl_link_stats64 *stats)
{
	struct nfp_net *nn = netdev_priv(netdev);
	int r;

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
}