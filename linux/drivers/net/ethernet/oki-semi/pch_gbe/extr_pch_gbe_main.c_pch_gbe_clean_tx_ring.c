#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pch_gbe_tx_ring {unsigned int count; unsigned long size; int dma; scalar_t__ next_to_clean; scalar_t__ next_to_use; struct pch_gbe_buffer* desc; struct pch_gbe_buffer* buffer_info; } ;
struct pch_gbe_hw {TYPE_1__* reg; } ;
struct pch_gbe_buffer {int dummy; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; struct pch_gbe_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  TX_DSC_SIZE; int /*<<< orphan*/  TX_DSC_HW_P; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct pch_gbe_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  pch_gbe_unmap_and_free_tx_resource (struct pch_gbe_adapter*,struct pch_gbe_buffer*) ; 

__attribute__((used)) static void pch_gbe_clean_tx_ring(struct pch_gbe_adapter *adapter,
				   struct pch_gbe_tx_ring *tx_ring)
{
	struct pch_gbe_hw *hw = &adapter->hw;
	struct pch_gbe_buffer *buffer_info;
	unsigned long size;
	unsigned int i;

	/* Free all the Tx ring sk_buffs */
	for (i = 0; i < tx_ring->count; i++) {
		buffer_info = &tx_ring->buffer_info[i];
		pch_gbe_unmap_and_free_tx_resource(adapter, buffer_info);
	}
	netdev_dbg(adapter->netdev,
		   "call pch_gbe_unmap_and_free_tx_resource() %d count\n", i);

	size = (unsigned long)sizeof(struct pch_gbe_buffer) * tx_ring->count;
	memset(tx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	memset(tx_ring->desc, 0, tx_ring->size);
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	iowrite32(tx_ring->dma, &hw->reg->TX_DSC_HW_P);
	iowrite32((tx_ring->size - 0x10), &hw->reg->TX_DSC_SIZE);
}