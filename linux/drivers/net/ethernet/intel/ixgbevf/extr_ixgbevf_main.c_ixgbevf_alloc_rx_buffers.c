#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ length; } ;
struct TYPE_6__ {TYPE_2__ upper; } ;
struct TYPE_4__ {int /*<<< orphan*/  pkt_addr; } ;
union ixgbe_adv_rx_desc {TYPE_3__ wb; TYPE_1__ read; } ;
typedef  scalar_t__ u16 ;
struct ixgbevf_rx_buffer {scalar_t__ page_offset; scalar_t__ dma; } ;
struct ixgbevf_ring {unsigned int next_to_use; unsigned int next_to_alloc; scalar_t__ count; struct ixgbevf_rx_buffer* rx_buffer_info; int /*<<< orphan*/  dev; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 union ixgbe_adv_rx_desc* IXGBEVF_RX_DESC (struct ixgbevf_ring*,unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_device (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_alloc_mapped_page (struct ixgbevf_ring*,struct ixgbevf_rx_buffer*) ; 
 int /*<<< orphan*/  ixgbevf_rx_bufsz (struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  ixgbevf_write_tail (struct ixgbevf_ring*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void ixgbevf_alloc_rx_buffers(struct ixgbevf_ring *rx_ring,
				     u16 cleaned_count)
{
	union ixgbe_adv_rx_desc *rx_desc;
	struct ixgbevf_rx_buffer *bi;
	unsigned int i = rx_ring->next_to_use;

	/* nothing to do or no valid netdev defined */
	if (!cleaned_count || !rx_ring->netdev)
		return;

	rx_desc = IXGBEVF_RX_DESC(rx_ring, i);
	bi = &rx_ring->rx_buffer_info[i];
	i -= rx_ring->count;

	do {
		if (!ixgbevf_alloc_mapped_page(rx_ring, bi))
			break;

		/* sync the buffer for use by the device */
		dma_sync_single_range_for_device(rx_ring->dev, bi->dma,
						 bi->page_offset,
						 ixgbevf_rx_bufsz(rx_ring),
						 DMA_FROM_DEVICE);

		/* Refresh the desc even if pkt_addr didn't change
		 * because each write-back erases this info.
		 */
		rx_desc->read.pkt_addr = cpu_to_le64(bi->dma + bi->page_offset);

		rx_desc++;
		bi++;
		i++;
		if (unlikely(!i)) {
			rx_desc = IXGBEVF_RX_DESC(rx_ring, 0);
			bi = rx_ring->rx_buffer_info;
			i -= rx_ring->count;
		}

		/* clear the length for the next_to_use descriptor */
		rx_desc->wb.upper.length = 0;

		cleaned_count--;
	} while (cleaned_count);

	i += rx_ring->count;

	if (rx_ring->next_to_use != i) {
		/* record the next descriptor to use */
		rx_ring->next_to_use = i;

		/* update next to alloc since we have filled the ring */
		rx_ring->next_to_alloc = i;

		/* Force memory writes to complete before letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable for weak-ordered memory model archs,
		 * such as IA-64).
		 */
		wmb();
		ixgbevf_write_tail(rx_ring, i);
	}
}