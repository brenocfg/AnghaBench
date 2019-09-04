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
struct pci_dev {int dummy; } ;
struct atl1_rrd_ring {int /*<<< orphan*/  next_to_clean; scalar_t__ next_to_use; } ;
struct atl1_rfd_ring {unsigned int count; unsigned long size; int /*<<< orphan*/  next_to_use; scalar_t__ next_to_clean; struct atl1_buffer* desc; struct atl1_buffer* buffer_info; } ;
struct atl1_buffer {int /*<<< orphan*/ * skb; scalar_t__ dma; int /*<<< orphan*/  length; } ;
struct atl1_adapter {struct pci_dev* pdev; struct atl1_rrd_ring rrd_ring; struct atl1_rfd_ring rfd_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct atl1_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1_clean_rx_ring(struct atl1_adapter *adapter)
{
	struct atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	struct atl1_rrd_ring *rrd_ring = &adapter->rrd_ring;
	struct atl1_buffer *buffer_info;
	struct pci_dev *pdev = adapter->pdev;
	unsigned long size;
	unsigned int i;

	/* Free all the Rx ring sk_buffs */
	for (i = 0; i < rfd_ring->count; i++) {
		buffer_info = &rfd_ring->buffer_info[i];
		if (buffer_info->dma) {
			pci_unmap_page(pdev, buffer_info->dma,
				buffer_info->length, PCI_DMA_FROMDEVICE);
			buffer_info->dma = 0;
		}
		if (buffer_info->skb) {
			dev_kfree_skb(buffer_info->skb);
			buffer_info->skb = NULL;
		}
	}

	size = sizeof(struct atl1_buffer) * rfd_ring->count;
	memset(rfd_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	memset(rfd_ring->desc, 0, rfd_ring->size);

	rfd_ring->next_to_clean = 0;
	atomic_set(&rfd_ring->next_to_use, 0);

	rrd_ring->next_to_use = 0;
	atomic_set(&rrd_ring->next_to_clean, 0);
}