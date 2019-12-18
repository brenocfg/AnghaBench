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
struct ena_ring {int /*<<< orphan*/ * push_buf_intermediate_buf; int /*<<< orphan*/ * free_ids; int /*<<< orphan*/ * tx_buffer_info; } ;
struct ena_adapter {struct ena_ring* tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ena_free_tx_resources(struct ena_adapter *adapter, int qid)
{
	struct ena_ring *tx_ring = &adapter->tx_ring[qid];

	vfree(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = NULL;

	vfree(tx_ring->free_ids);
	tx_ring->free_ids = NULL;

	vfree(tx_ring->push_buf_intermediate_buf);
	tx_ring->push_buf_intermediate_buf = NULL;
}