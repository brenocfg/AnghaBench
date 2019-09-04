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
typedef  size_t u16 ;
struct pci_dev {int dummy; } ;
struct atl1e_tx_ring {size_t count; struct atl1e_tx_buffer* tx_buffer; struct atl1e_tx_buffer* desc; } ;
struct atl1e_tx_buffer {int flags; int /*<<< orphan*/ * skb; scalar_t__ dma; int /*<<< orphan*/  length; } ;
struct atl1e_tpd_desc {int dummy; } ;
struct atl1e_adapter {struct pci_dev* pdev; struct atl1e_tx_ring tx_ring; } ;

/* Variables and functions */
 int ATL1E_TX_PCIMAP_PAGE ; 
 int ATL1E_TX_PCIMAP_SINGLE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct atl1e_tx_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atl1e_clean_tx_ring(struct atl1e_adapter *adapter)
{
	struct atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	struct atl1e_tx_buffer *tx_buffer = NULL;
	struct pci_dev *pdev = adapter->pdev;
	u16 index, ring_count;

	if (tx_ring->desc == NULL || tx_ring->tx_buffer == NULL)
		return;

	ring_count = tx_ring->count;
	/* first unmmap dma */
	for (index = 0; index < ring_count; index++) {
		tx_buffer = &tx_ring->tx_buffer[index];
		if (tx_buffer->dma) {
			if (tx_buffer->flags & ATL1E_TX_PCIMAP_SINGLE)
				pci_unmap_single(pdev, tx_buffer->dma,
					tx_buffer->length, PCI_DMA_TODEVICE);
			else if (tx_buffer->flags & ATL1E_TX_PCIMAP_PAGE)
				pci_unmap_page(pdev, tx_buffer->dma,
					tx_buffer->length, PCI_DMA_TODEVICE);
			tx_buffer->dma = 0;
		}
	}
	/* second free skb */
	for (index = 0; index < ring_count; index++) {
		tx_buffer = &tx_ring->tx_buffer[index];
		if (tx_buffer->skb) {
			dev_kfree_skb_any(tx_buffer->skb);
			tx_buffer->skb = NULL;
		}
	}
	/* Zero out Tx-buffers */
	memset(tx_ring->desc, 0, sizeof(struct atl1e_tpd_desc) *
				ring_count);
	memset(tx_ring->tx_buffer, 0, sizeof(struct atl1e_tx_buffer) *
				ring_count);
}