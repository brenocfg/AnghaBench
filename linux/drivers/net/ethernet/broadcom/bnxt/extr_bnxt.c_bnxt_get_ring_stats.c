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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; } ;
struct ctx_hw_stats {int /*<<< orphan*/  tx_drop_pkts; int /*<<< orphan*/  rx_mcast_pkts; int /*<<< orphan*/  rx_discard_pkts; int /*<<< orphan*/  tx_bcast_bytes; int /*<<< orphan*/  tx_mcast_bytes; int /*<<< orphan*/  tx_ucast_bytes; int /*<<< orphan*/  rx_bcast_bytes; int /*<<< orphan*/  rx_mcast_bytes; int /*<<< orphan*/  rx_ucast_bytes; int /*<<< orphan*/  tx_bcast_pkts; int /*<<< orphan*/  tx_mcast_pkts; int /*<<< orphan*/  tx_ucast_pkts; int /*<<< orphan*/  rx_bcast_pkts; int /*<<< orphan*/  rx_ucast_pkts; } ;
struct bnxt_cp_ring_info {struct ctx_hw_stats* hw_stats; } ;
struct bnxt_napi {struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int cp_nr_rings; struct bnxt_napi** bnapi; } ;

/* Variables and functions */
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_get_ring_stats(struct bnxt *bp,
				struct rtnl_link_stats64 *stats)
{
	int i;


	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
		struct ctx_hw_stats *hw_stats = cpr->hw_stats;

		stats->rx_packets += le64_to_cpu(hw_stats->rx_ucast_pkts);
		stats->rx_packets += le64_to_cpu(hw_stats->rx_mcast_pkts);
		stats->rx_packets += le64_to_cpu(hw_stats->rx_bcast_pkts);

		stats->tx_packets += le64_to_cpu(hw_stats->tx_ucast_pkts);
		stats->tx_packets += le64_to_cpu(hw_stats->tx_mcast_pkts);
		stats->tx_packets += le64_to_cpu(hw_stats->tx_bcast_pkts);

		stats->rx_bytes += le64_to_cpu(hw_stats->rx_ucast_bytes);
		stats->rx_bytes += le64_to_cpu(hw_stats->rx_mcast_bytes);
		stats->rx_bytes += le64_to_cpu(hw_stats->rx_bcast_bytes);

		stats->tx_bytes += le64_to_cpu(hw_stats->tx_ucast_bytes);
		stats->tx_bytes += le64_to_cpu(hw_stats->tx_mcast_bytes);
		stats->tx_bytes += le64_to_cpu(hw_stats->tx_bcast_bytes);

		stats->rx_missed_errors +=
			le64_to_cpu(hw_stats->rx_discard_pkts);

		stats->multicast += le64_to_cpu(hw_stats->rx_mcast_pkts);

		stats->tx_dropped += le64_to_cpu(hw_stats->tx_drop_pkts);
	}
}