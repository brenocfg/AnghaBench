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
struct hinic_rxq_stats {int /*<<< orphan*/  syncp; scalar_t__ other_errors; scalar_t__ csum_errors; scalar_t__ errors; scalar_t__ pkts; scalar_t__ bytes; } ;
struct hinic_rxq {int dummy; } ;
struct hinic_dev {struct hinic_rxq_stats rx_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_rxq_clean_stats (struct hinic_rxq*) ; 
 int /*<<< orphan*/  hinic_rxq_get_stats (struct hinic_rxq*,struct hinic_rxq_stats*) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_rx_stats(struct hinic_dev *nic_dev, struct hinic_rxq *rxq)
{
	struct hinic_rxq_stats *nic_rx_stats = &nic_dev->rx_stats;
	struct hinic_rxq_stats rx_stats;

	u64_stats_init(&rx_stats.syncp);

	hinic_rxq_get_stats(rxq, &rx_stats);

	u64_stats_update_begin(&nic_rx_stats->syncp);
	nic_rx_stats->bytes += rx_stats.bytes;
	nic_rx_stats->pkts  += rx_stats.pkts;
	nic_rx_stats->errors += rx_stats.errors;
	nic_rx_stats->csum_errors += rx_stats.csum_errors;
	nic_rx_stats->other_errors += rx_stats.other_errors;
	u64_stats_update_end(&nic_rx_stats->syncp);

	hinic_rxq_clean_stats(rxq);
}