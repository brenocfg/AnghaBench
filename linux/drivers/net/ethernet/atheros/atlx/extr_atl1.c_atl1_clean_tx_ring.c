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
struct atl1_tpd_ring {unsigned int count; unsigned long size; int /*<<< orphan*/  next_to_clean; int /*<<< orphan*/  next_to_use; struct atl1_buffer* desc; struct atl1_buffer* buffer_info; } ;
struct atl1_buffer {int /*<<< orphan*/ * skb; scalar_t__ dma; int /*<<< orphan*/  length; } ;
struct atl1_adapter {struct pci_dev* pdev; struct atl1_tpd_ring tpd_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct atl1_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1_clean_tx_ring(struct atl1_adapter *adapter)
{
	struct atl1_tpd_ring *tpd_ring = &adapter->tpd_ring;
	struct atl1_buffer *buffer_info;
	struct pci_dev *pdev = adapter->pdev;
	unsigned long size;
	unsigned int i;

	/* Free all the Tx ring sk_buffs */
	for (i = 0; i < tpd_ring->count; i++) {
		buffer_info = &tpd_ring->buffer_info[i];
		if (buffer_info->dma) {
			pci_unmap_page(pdev, buffer_info->dma,
				buffer_info->length, PCI_DMA_TODEVICE);
			buffer_info->dma = 0;
		}
	}

	for (i = 0; i < tpd_ring->count; i++) {
		buffer_info = &tpd_ring->buffer_info[i];
		if (buffer_info->skb) {
			dev_kfree_skb_any(buffer_info->skb);
			buffer_info->skb = NULL;
		}
	}

	size = sizeof(struct atl1_buffer) * tpd_ring->count;
	memset(tpd_ring->buffer_info, 0, size);

	/* Zero out the descriptor ring */
	memset(tpd_ring->desc, 0, tpd_ring->size);

	atomic_set(&tpd_ring->next_to_use, 0);
	atomic_set(&tpd_ring->next_to_clean, 0);
}