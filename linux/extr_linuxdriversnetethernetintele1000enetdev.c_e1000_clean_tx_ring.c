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
struct e1000_ring {unsigned int count; unsigned long size; scalar_t__ next_to_clean; scalar_t__ next_to_use; struct e1000_buffer* desc; struct e1000_buffer* buffer_info; struct e1000_adapter* adapter; } ;
struct e1000_buffer {int dummy; } ;
struct e1000_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_put_txbuf (struct e1000_ring*,struct e1000_buffer*,int) ; 
 int /*<<< orphan*/  memset (struct e1000_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  netdev_reset_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e1000_clean_tx_ring(struct e1000_ring *tx_ring)
{
	struct e1000_adapter *adapter = tx_ring->adapter;
	struct e1000_buffer *buffer_info;
	unsigned long size;
	unsigned int i;

	for (i = 0; i < tx_ring->count; i++) {
		buffer_info = &tx_ring->buffer_info[i];
		e1000_put_txbuf(tx_ring, buffer_info, false);
	}

	netdev_reset_queue(adapter->netdev);
	size = sizeof(struct e1000_buffer) * tx_ring->count;
	memset(tx_ring->buffer_info, 0, size);

	memset(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
}