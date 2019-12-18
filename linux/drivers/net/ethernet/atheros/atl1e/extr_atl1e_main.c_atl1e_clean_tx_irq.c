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
struct atl1e_tx_ring {size_t count; int /*<<< orphan*/  next_to_clean; struct atl1e_tx_buffer* tx_buffer; } ;
struct atl1e_tx_buffer {int flags; int /*<<< orphan*/ * skb; scalar_t__ dma; int /*<<< orphan*/  length; } ;
struct atl1e_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  pdev; int /*<<< orphan*/  hw; struct atl1e_tx_ring tx_ring; } ;

/* Variables and functions */
 int ATL1E_TX_PCIMAP_PAGE ; 
 int ATL1E_TX_PCIMAP_SINGLE ; 
 size_t AT_READ_REGW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  REG_TPD_CONS_IDX ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dev_consume_skb_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool atl1e_clean_tx_irq(struct atl1e_adapter *adapter)
{
	struct atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	struct atl1e_tx_buffer *tx_buffer = NULL;
	u16 hw_next_to_clean = AT_READ_REGW(&adapter->hw, REG_TPD_CONS_IDX);
	u16 next_to_clean = atomic_read(&tx_ring->next_to_clean);

	while (next_to_clean != hw_next_to_clean) {
		tx_buffer = &tx_ring->tx_buffer[next_to_clean];
		if (tx_buffer->dma) {
			if (tx_buffer->flags & ATL1E_TX_PCIMAP_SINGLE)
				pci_unmap_single(adapter->pdev, tx_buffer->dma,
					tx_buffer->length, PCI_DMA_TODEVICE);
			else if (tx_buffer->flags & ATL1E_TX_PCIMAP_PAGE)
				pci_unmap_page(adapter->pdev, tx_buffer->dma,
					tx_buffer->length, PCI_DMA_TODEVICE);
			tx_buffer->dma = 0;
		}

		if (tx_buffer->skb) {
			dev_consume_skb_irq(tx_buffer->skb);
			tx_buffer->skb = NULL;
		}

		if (++next_to_clean == tx_ring->count)
			next_to_clean = 0;
	}

	atomic_set(&tx_ring->next_to_clean, next_to_clean);

	if (netif_queue_stopped(adapter->netdev) &&
			netif_carrier_ok(adapter->netdev)) {
		netif_wake_queue(adapter->netdev);
	}

	return true;
}