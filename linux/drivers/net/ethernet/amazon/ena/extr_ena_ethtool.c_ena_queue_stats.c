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
typedef  int /*<<< orphan*/  u64 ;
struct ena_stats {scalar_t__ stat_offset; } ;
struct ena_ring {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_stats; int /*<<< orphan*/  tx_stats; } ;
struct ena_adapter {int num_queues; struct ena_ring* rx_ring; struct ena_ring* tx_ring; } ;

/* Variables and functions */
 int ENA_STATS_ARRAY_RX ; 
 int ENA_STATS_ARRAY_TX ; 
 int /*<<< orphan*/  ena_safe_update_stat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ena_stats* ena_stats_rx_strings ; 
 struct ena_stats* ena_stats_tx_strings ; 

__attribute__((used)) static void ena_queue_stats(struct ena_adapter *adapter, u64 **data)
{
	const struct ena_stats *ena_stats;
	struct ena_ring *ring;

	u64 *ptr;
	int i, j;

	for (i = 0; i < adapter->num_queues; i++) {
		/* Tx stats */
		ring = &adapter->tx_ring[i];

		for (j = 0; j < ENA_STATS_ARRAY_TX; j++) {
			ena_stats = &ena_stats_tx_strings[j];

			ptr = (u64 *)((uintptr_t)&ring->tx_stats +
				(uintptr_t)ena_stats->stat_offset);

			ena_safe_update_stat(ptr, (*data)++, &ring->syncp);
		}

		/* Rx stats */
		ring = &adapter->rx_ring[i];

		for (j = 0; j < ENA_STATS_ARRAY_RX; j++) {
			ena_stats = &ena_stats_rx_strings[j];

			ptr = (u64 *)((uintptr_t)&ring->rx_stats +
				(uintptr_t)ena_stats->stat_offset);

			ena_safe_update_stat(ptr, (*data)++, &ring->syncp);
		}
	}
}