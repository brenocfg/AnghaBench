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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ixgb_desc_ring {unsigned int count; unsigned long size; scalar_t__ next_to_use; scalar_t__ next_to_clean; struct ixgb_buffer* desc; struct ixgb_buffer* buffer_info; } ;
struct ixgb_buffer {int /*<<< orphan*/ * skb; scalar_t__ length; scalar_t__ dma; } ;
struct ixgb_adapter {int /*<<< orphan*/  hw; struct pci_dev* pdev; struct ixgb_desc_ring rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDH ; 
 int /*<<< orphan*/  RDT ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ixgb_buffer*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void
ixgb_clean_rx_ring(struct ixgb_adapter *adapter)
{
	struct ixgb_desc_ring *rx_ring = &adapter->rx_ring;
	struct ixgb_buffer *buffer_info;
	struct pci_dev *pdev = adapter->pdev;
	unsigned long size;
	unsigned int i;

	/* Free all the Rx ring sk_buffs */

	for (i = 0; i < rx_ring->count; i++) {
		buffer_info = &rx_ring->buffer_info[i];
		if (buffer_info->dma) {
			dma_unmap_single(&pdev->dev,
					 buffer_info->dma,
					 buffer_info->length,
					 DMA_FROM_DEVICE);
			buffer_info->dma = 0;
			buffer_info->length = 0;
		}

		if (buffer_info->skb) {
			dev_kfree_skb(buffer_info->skb);
			buffer_info->skb = NULL;
		}
	}

	size = sizeof(struct ixgb_buffer) * rx_ring->count;
	memset(rx_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */

	memset(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;

	IXGB_WRITE_REG(&adapter->hw, RDH, 0);
	IXGB_WRITE_REG(&adapter->hw, RDT, 0);
}