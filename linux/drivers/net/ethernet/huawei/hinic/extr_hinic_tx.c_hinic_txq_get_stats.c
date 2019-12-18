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
struct hinic_txq_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  big_frags_pkts; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_wake; int /*<<< orphan*/  tx_busy; int /*<<< orphan*/  bytes; int /*<<< orphan*/  pkts; } ;
struct hinic_txq {struct hinic_txq_stats txq_stats; } ;

/* Variables and functions */
 unsigned int u64_stats_fetch_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

void hinic_txq_get_stats(struct hinic_txq *txq, struct hinic_txq_stats *stats)
{
	struct hinic_txq_stats *txq_stats = &txq->txq_stats;
	unsigned int start;

	u64_stats_update_begin(&stats->syncp);
	do {
		start = u64_stats_fetch_begin(&txq_stats->syncp);
		stats->pkts    = txq_stats->pkts;
		stats->bytes   = txq_stats->bytes;
		stats->tx_busy = txq_stats->tx_busy;
		stats->tx_wake = txq_stats->tx_wake;
		stats->tx_dropped = txq_stats->tx_dropped;
		stats->big_frags_pkts = txq_stats->big_frags_pkts;
	} while (u64_stats_fetch_retry(&txq_stats->syncp, start));
	u64_stats_update_end(&stats->syncp);
}