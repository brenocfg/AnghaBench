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
struct hinic_txq_stats {int /*<<< orphan*/  syncp; scalar_t__ big_frags_pkts; scalar_t__ tx_dropped; scalar_t__ tx_wake; scalar_t__ tx_busy; scalar_t__ bytes; scalar_t__ pkts; } ;
struct hinic_txq {struct hinic_txq_stats txq_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

void hinic_txq_clean_stats(struct hinic_txq *txq)
{
	struct hinic_txq_stats *txq_stats = &txq->txq_stats;

	u64_stats_update_begin(&txq_stats->syncp);
	txq_stats->pkts    = 0;
	txq_stats->bytes   = 0;
	txq_stats->tx_busy = 0;
	txq_stats->tx_wake = 0;
	txq_stats->tx_dropped = 0;
	txq_stats->big_frags_pkts = 0;
	u64_stats_update_end(&txq_stats->syncp);
}