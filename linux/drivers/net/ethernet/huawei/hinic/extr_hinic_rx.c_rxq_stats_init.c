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
struct hinic_rxq_stats {int /*<<< orphan*/  syncp; } ;
struct hinic_rxq {struct hinic_rxq_stats rxq_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  hinic_rxq_clean_stats (struct hinic_rxq*) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxq_stats_init(struct hinic_rxq *rxq)
{
	struct hinic_rxq_stats *rxq_stats = &rxq->rxq_stats;

	u64_stats_init(&rxq_stats->syncp);
	hinic_rxq_clean_stats(rxq);
}