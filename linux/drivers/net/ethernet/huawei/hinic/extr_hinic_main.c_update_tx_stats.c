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
struct hinic_txq_stats {int /*<<< orphan*/  syncp; scalar_t__ big_frags_pkts; scalar_t__ tx_dropped; scalar_t__ tx_wake; scalar_t__ tx_busy; scalar_t__ pkts; scalar_t__ bytes; } ;
struct hinic_txq {int dummy; } ;
struct hinic_dev {struct hinic_txq_stats tx_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_txq_clean_stats (struct hinic_txq*) ; 
 int /*<<< orphan*/  hinic_txq_get_stats (struct hinic_txq*,struct hinic_txq_stats*) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_tx_stats(struct hinic_dev *nic_dev, struct hinic_txq *txq)
{
	struct hinic_txq_stats *nic_tx_stats = &nic_dev->tx_stats;
	struct hinic_txq_stats tx_stats;

	u64_stats_init(&tx_stats.syncp);

	hinic_txq_get_stats(txq, &tx_stats);

	u64_stats_update_begin(&nic_tx_stats->syncp);
	nic_tx_stats->bytes += tx_stats.bytes;
	nic_tx_stats->pkts += tx_stats.pkts;
	nic_tx_stats->tx_busy += tx_stats.tx_busy;
	nic_tx_stats->tx_wake += tx_stats.tx_wake;
	nic_tx_stats->tx_dropped += tx_stats.tx_dropped;
	nic_tx_stats->big_frags_pkts += tx_stats.big_frags_pkts;
	u64_stats_update_end(&nic_tx_stats->syncp);

	hinic_txq_clean_stats(txq);
}