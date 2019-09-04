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
typedef  int /*<<< orphan*/  u16 ;
struct ena_tx_buffer {int dummy; } ;
struct ena_ring {int ring_size; int* free_tx_ids; int /*<<< orphan*/  cpu; scalar_t__ next_to_clean; scalar_t__ next_to_use; int /*<<< orphan*/  tx_stats; void* tx_buffer_info; } ;
struct ena_irq {int /*<<< orphan*/  cpu; } ;
struct ena_adapter {int /*<<< orphan*/  netdev; struct ena_irq* irq_tbl; struct ena_ring* tx_ring; } ;

/* Variables and functions */
 int EEXIST ; 
 size_t ENA_IO_IRQ_IDX (int) ; 
 int ENOMEM ; 
 int cpu_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  netif_err (struct ena_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vzalloc (int) ; 
 void* vzalloc_node (int,int) ; 

__attribute__((used)) static int ena_setup_tx_resources(struct ena_adapter *adapter, int qid)
{
	struct ena_ring *tx_ring = &adapter->tx_ring[qid];
	struct ena_irq *ena_irq = &adapter->irq_tbl[ENA_IO_IRQ_IDX(qid)];
	int size, i, node;

	if (tx_ring->tx_buffer_info) {
		netif_err(adapter, ifup,
			  adapter->netdev, "tx_buffer_info info is not NULL");
		return -EEXIST;
	}

	size = sizeof(struct ena_tx_buffer) * tx_ring->ring_size;
	node = cpu_to_node(ena_irq->cpu);

	tx_ring->tx_buffer_info = vzalloc_node(size, node);
	if (!tx_ring->tx_buffer_info) {
		tx_ring->tx_buffer_info = vzalloc(size);
		if (!tx_ring->tx_buffer_info)
			return -ENOMEM;
	}

	size = sizeof(u16) * tx_ring->ring_size;
	tx_ring->free_tx_ids = vzalloc_node(size, node);
	if (!tx_ring->free_tx_ids) {
		tx_ring->free_tx_ids = vzalloc(size);
		if (!tx_ring->free_tx_ids) {
			vfree(tx_ring->tx_buffer_info);
			return -ENOMEM;
		}
	}

	/* Req id ring for TX out of order completions */
	for (i = 0; i < tx_ring->ring_size; i++)
		tx_ring->free_tx_ids[i] = i;

	/* Reset tx statistics */
	memset(&tx_ring->tx_stats, 0x0, sizeof(tx_ring->tx_stats));

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	tx_ring->cpu = ena_irq->cpu;
	return 0;
}