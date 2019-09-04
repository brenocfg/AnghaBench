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
struct ixgb_desc_ring {unsigned int count; unsigned long size; scalar_t__ next_to_clean; scalar_t__ next_to_use; struct ixgb_buffer* desc; struct ixgb_buffer* buffer_info; } ;
struct ixgb_buffer {int dummy; } ;
struct ixgb_adapter {int /*<<< orphan*/  hw; struct ixgb_desc_ring tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGB_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDH ; 
 int /*<<< orphan*/  TDT ; 
 int /*<<< orphan*/  ixgb_unmap_and_free_tx_resource (struct ixgb_adapter*,struct ixgb_buffer*) ; 
 int /*<<< orphan*/  memset (struct ixgb_buffer*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void
ixgb_clean_tx_ring(struct ixgb_adapter *adapter)
{
	struct ixgb_desc_ring *tx_ring = &adapter->tx_ring;
	struct ixgb_buffer *buffer_info;
	unsigned long size;
	unsigned int i;

	/* Free all the Tx ring sk_buffs */

	for (i = 0; i < tx_ring->count; i++) {
		buffer_info = &tx_ring->buffer_info[i];
		ixgb_unmap_and_free_tx_resource(adapter, buffer_info);
	}

	size = sizeof(struct ixgb_buffer) * tx_ring->count;
	memset(tx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */

	memset(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	IXGB_WRITE_REG(&adapter->hw, TDH, 0);
	IXGB_WRITE_REG(&adapter->hw, TDT, 0);
}