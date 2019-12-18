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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct rtw_pci_tx_ring {int /*<<< orphan*/  queue; } ;
struct rtw_pci_tx_data {int /*<<< orphan*/  dma; } ;
struct rtw_pci {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtw_pci_tx_data* rtw_pci_get_tx_data (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtw_pci_release_rsvd_page(struct rtw_pci *rtwpci,
				      struct rtw_pci_tx_ring *ring)
{
	struct sk_buff *prev = skb_dequeue(&ring->queue);
	struct rtw_pci_tx_data *tx_data;
	dma_addr_t dma;

	if (!prev)
		return;

	tx_data = rtw_pci_get_tx_data(prev);
	dma = tx_data->dma;
	pci_unmap_single(rtwpci->pdev, dma, prev->len,
			 PCI_DMA_TODEVICE);
	dev_kfree_skb_any(prev);
}