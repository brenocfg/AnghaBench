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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct e1000_rx_ring {unsigned int next_to_use; unsigned int count; scalar_t__ rdt; struct e1000_rx_buffer* buffer_info; } ;
struct e1000_rx_desc {int /*<<< orphan*/  buffer_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct e1000_rx_buffer {scalar_t__ dma; TYPE_1__ rxbuf; } ;
struct e1000_hw {scalar_t__ hw_addr; } ;
struct e1000_adapter {unsigned int rx_buffer_len; int /*<<< orphan*/  alloc_rx_buff_failed; struct pci_dev* pdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 struct e1000_rx_desc* E1000_RX_DESC (struct e1000_rx_ring,unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,void*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 void* e1000_alloc_frag (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_check_64k_bound (struct e1000_adapter*,void*,unsigned int) ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*,unsigned int,void*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  skb_free_frag (void*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void e1000_alloc_rx_buffers(struct e1000_adapter *adapter,
				   struct e1000_rx_ring *rx_ring,
				   int cleaned_count)
{
	struct e1000_hw *hw = &adapter->hw;
	struct pci_dev *pdev = adapter->pdev;
	struct e1000_rx_desc *rx_desc;
	struct e1000_rx_buffer *buffer_info;
	unsigned int i;
	unsigned int bufsz = adapter->rx_buffer_len;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	while (cleaned_count--) {
		void *data;

		if (buffer_info->rxbuf.data)
			goto skip;

		data = e1000_alloc_frag(adapter);
		if (!data) {
			/* Better luck next round */
			adapter->alloc_rx_buff_failed++;
			break;
		}

		/* Fix for errata 23, can't cross 64kB boundary */
		if (!e1000_check_64k_bound(adapter, data, bufsz)) {
			void *olddata = data;
			e_err(rx_err, "skb align check failed: %u bytes at "
			      "%p\n", bufsz, data);
			/* Try again, without freeing the previous */
			data = e1000_alloc_frag(adapter);
			/* Failed allocation, critical failure */
			if (!data) {
				skb_free_frag(olddata);
				adapter->alloc_rx_buff_failed++;
				break;
			}

			if (!e1000_check_64k_bound(adapter, data, bufsz)) {
				/* give up */
				skb_free_frag(data);
				skb_free_frag(olddata);
				adapter->alloc_rx_buff_failed++;
				break;
			}

			/* Use new allocation */
			skb_free_frag(olddata);
		}
		buffer_info->dma = dma_map_single(&pdev->dev,
						  data,
						  adapter->rx_buffer_len,
						  DMA_FROM_DEVICE);
		if (dma_mapping_error(&pdev->dev, buffer_info->dma)) {
			skb_free_frag(data);
			buffer_info->dma = 0;
			adapter->alloc_rx_buff_failed++;
			break;
		}

		/* XXX if it was allocated cleanly it will never map to a
		 * boundary crossing
		 */

		/* Fix for errata 23, can't cross 64kB boundary */
		if (!e1000_check_64k_bound(adapter,
					(void *)(unsigned long)buffer_info->dma,
					adapter->rx_buffer_len)) {
			e_err(rx_err, "dma align check failed: %u bytes at "
			      "%p\n", adapter->rx_buffer_len,
			      (void *)(unsigned long)buffer_info->dma);

			dma_unmap_single(&pdev->dev, buffer_info->dma,
					 adapter->rx_buffer_len,
					 DMA_FROM_DEVICE);

			skb_free_frag(data);
			buffer_info->rxbuf.data = NULL;
			buffer_info->dma = 0;

			adapter->alloc_rx_buff_failed++;
			break;
		}
		buffer_info->rxbuf.data = data;
 skip:
		rx_desc = E1000_RX_DESC(*rx_ring, i);
		rx_desc->buffer_addr = cpu_to_le64(buffer_info->dma);

		if (unlikely(++i == rx_ring->count))
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	}

	if (likely(rx_ring->next_to_use != i)) {
		rx_ring->next_to_use = i;
		if (unlikely(i-- == 0))
			i = (rx_ring->count - 1);

		/* Force memory writes to complete before letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable for weak-ordered memory model archs,
		 * such as IA-64).
		 */
		dma_wmb();
		writel(i, hw->hw_addr + rx_ring->rdt);
	}
}