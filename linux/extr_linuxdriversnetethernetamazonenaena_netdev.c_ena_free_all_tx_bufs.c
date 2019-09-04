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
struct ena_ring {int dummy; } ;
struct ena_adapter {int num_queues; struct ena_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  ena_free_tx_bufs (struct ena_ring*) ; 

__attribute__((used)) static void ena_free_all_tx_bufs(struct ena_adapter *adapter)
{
	struct ena_ring *tx_ring;
	int i;

	for (i = 0; i < adapter->num_queues; i++) {
		tx_ring = &adapter->tx_ring[i];
		ena_free_tx_bufs(tx_ring);
	}
}