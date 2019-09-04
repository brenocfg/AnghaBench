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
struct e1000_tx_ring {unsigned int count; unsigned long size; int last_tx_tso; scalar_t__ tdt; scalar_t__ tdh; scalar_t__ next_to_clean; scalar_t__ next_to_use; struct e1000_tx_buffer* desc; struct e1000_tx_buffer* buffer_info; } ;
struct e1000_tx_buffer {int dummy; } ;
struct e1000_hw {scalar_t__ hw_addr; } ;
struct e1000_adapter {int /*<<< orphan*/  netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_unmap_and_free_tx_resource (struct e1000_adapter*,struct e1000_tx_buffer*) ; 
 int /*<<< orphan*/  memset (struct e1000_tx_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  netdev_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void e1000_clean_tx_ring(struct e1000_adapter *adapter,
				struct e1000_tx_ring *tx_ring)
{
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_tx_buffer *buffer_info;
	unsigned long size;
	unsigned int i;

	/* Free all the Tx ring sk_buffs */

	for (i = 0; i < tx_ring->count; i++) {
		buffer_info = &tx_ring->buffer_info[i];
		e1000_unmap_and_free_tx_resource(adapter, buffer_info);
	}

	netdev_reset_queue(adapter->netdev);
	size = sizeof(struct e1000_tx_buffer) * tx_ring->count;
	memset(tx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */

	memset(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	tx_ring->last_tx_tso = false;

	writel(0, hw->hw_addr + tx_ring->tdh);
	writel(0, hw->hw_addr + tx_ring->tdt);
}