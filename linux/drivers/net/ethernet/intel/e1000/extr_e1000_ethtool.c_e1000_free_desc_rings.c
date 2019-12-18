#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct e1000_tx_ring {int count; TYPE_2__* buffer_info; int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; } ;
struct e1000_rx_ring {int count; TYPE_2__* buffer_info; int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; } ;
struct e1000_adapter {struct pci_dev* pdev; struct e1000_rx_ring test_rx_ring; struct e1000_tx_ring test_tx_ring; } ;
struct TYPE_3__ {TYPE_2__* data; } ;
struct TYPE_4__ {TYPE_1__ rxbuf; scalar_t__ dma; int /*<<< orphan*/  skb; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  E1000_RXBUFFER_2048 ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void e1000_free_desc_rings(struct e1000_adapter *adapter)
{
	struct e1000_tx_ring *txdr = &adapter->test_tx_ring;
	struct e1000_rx_ring *rxdr = &adapter->test_rx_ring;
	struct pci_dev *pdev = adapter->pdev;
	int i;

	if (txdr->desc && txdr->buffer_info) {
		for (i = 0; i < txdr->count; i++) {
			if (txdr->buffer_info[i].dma)
				dma_unmap_single(&pdev->dev,
						 txdr->buffer_info[i].dma,
						 txdr->buffer_info[i].length,
						 DMA_TO_DEVICE);
			dev_kfree_skb(txdr->buffer_info[i].skb);
		}
	}

	if (rxdr->desc && rxdr->buffer_info) {
		for (i = 0; i < rxdr->count; i++) {
			if (rxdr->buffer_info[i].dma)
				dma_unmap_single(&pdev->dev,
						 rxdr->buffer_info[i].dma,
						 E1000_RXBUFFER_2048,
						 DMA_FROM_DEVICE);
			kfree(rxdr->buffer_info[i].rxbuf.data);
		}
	}

	if (txdr->desc) {
		dma_free_coherent(&pdev->dev, txdr->size, txdr->desc,
				  txdr->dma);
		txdr->desc = NULL;
	}
	if (rxdr->desc) {
		dma_free_coherent(&pdev->dev, rxdr->size, rxdr->desc,
				  rxdr->dma);
		rxdr->desc = NULL;
	}

	kfree(txdr->buffer_info);
	txdr->buffer_info = NULL;
	kfree(rxdr->buffer_info);
	rxdr->buffer_info = NULL;
}