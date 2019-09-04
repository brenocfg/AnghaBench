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
struct hinic_txq_stats {int /*<<< orphan*/  syncp; } ;
struct hinic_txq {struct hinic_txq_stats txq_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_txq_clean_stats (struct hinic_txq*) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void txq_stats_init(struct hinic_txq *txq)
{
	struct hinic_txq_stats *txq_stats = &txq->txq_stats;

	u64_stats_init(&txq_stats->syncp);
	hinic_txq_clean_stats(txq);
}