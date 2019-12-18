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
struct e1000_rx_ring {unsigned int count; unsigned long size; scalar_t__ rdt; scalar_t__ rdh; scalar_t__ next_to_use; scalar_t__ next_to_clean; struct e1000_rx_buffer* desc; struct e1000_rx_buffer* buffer_info; int /*<<< orphan*/ * rx_skb_top; } ;
struct TYPE_2__ {int /*<<< orphan*/ * page; int /*<<< orphan*/ * data; } ;
struct e1000_rx_buffer {scalar_t__ dma; TYPE_1__ rxbuf; } ;
struct e1000_hw {scalar_t__ hw_addr; } ;
struct e1000_adapter {scalar_t__ clean_rx; int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_buffer_len; struct pci_dev* pdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_clean_jumbo_rx_irq ; 
 scalar_t__ e1000_clean_rx_irq ; 
 int /*<<< orphan*/  memset (struct e1000_rx_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  napi_free_frags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_free_frag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void e1000_clean_rx_ring(struct e1000_adapter *adapter,
				struct e1000_rx_ring *rx_ring)
{
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_rx_buffer *buffer_info;
	struct pci_dev *pdev = adapter->pdev;
	unsigned long size;
	unsigned int i;

	/* Free all the Rx netfrags */
	for (i = 0; i < rx_ring->count; i++) {
		buffer_info = &rx_ring->buffer_info[i];
		if (adapter->clean_rx == e1000_clean_rx_irq) {
			if (buffer_info->dma)
				dma_unmap_single(&pdev->dev, buffer_info->dma,
						 adapter->rx_buffer_len,
						 DMA_FROM_DEVICE);
			if (buffer_info->rxbuf.data) {
				skb_free_frag(buffer_info->rxbuf.data);
				buffer_info->rxbuf.data = NULL;
			}
		} else if (adapter->clean_rx == e1000_clean_jumbo_rx_irq) {
			if (buffer_info->dma)
				dma_unmap_page(&pdev->dev, buffer_info->dma,
					       adapter->rx_buffer_len,
					       DMA_FROM_DEVICE);
			if (buffer_info->rxbuf.page) {
				put_page(buffer_info->rxbuf.page);
				buffer_info->rxbuf.page = NULL;
			}
		}

		buffer_info->dma = 0;
	}

	/* there also may be some cached data from a chained receive */
	napi_free_frags(&adapter->napi);
	rx_ring->rx_skb_top = NULL;

	size = sizeof(struct e1000_rx_buffer) * rx_ring->count;
	memset(rx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	memset(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	writel(0, hw->hw_addr + rx_ring->rdh);
	writel(0, hw->hw_addr + rx_ring->rdt);
}