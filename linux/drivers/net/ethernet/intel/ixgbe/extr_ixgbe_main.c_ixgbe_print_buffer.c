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
struct ixgbe_tx_buffer {scalar_t__ time_stamp; int /*<<< orphan*/  next_to_watch; } ;
struct ixgbe_ring {size_t next_to_clean; int /*<<< orphan*/  next_to_use; struct ixgbe_tx_buffer* tx_buffer_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma ; 
 scalar_t__ dma_unmap_addr (struct ixgbe_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct ixgbe_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_print_buffer(struct ixgbe_ring *ring, int n)
{
	struct ixgbe_tx_buffer *tx_buffer;

	tx_buffer = &ring->tx_buffer_info[ring->next_to_clean];
	pr_info(" %5d %5X %5X %016llX %08X %p %016llX\n",
		n, ring->next_to_use, ring->next_to_clean,
		(u64)dma_unmap_addr(tx_buffer, dma),
		dma_unmap_len(tx_buffer, len),
		tx_buffer->next_to_watch,
		(u64)tx_buffer->time_stamp);
}