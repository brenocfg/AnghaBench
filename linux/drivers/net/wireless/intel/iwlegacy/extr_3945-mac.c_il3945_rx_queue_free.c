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
struct il_rx_queue {int /*<<< orphan*/ * rb_stts; int /*<<< orphan*/ * bd; int /*<<< orphan*/  rb_stts_dma; int /*<<< orphan*/  bd_dma; TYPE_2__* pool; } ;
struct il_rb_status {int dummy; } ;
struct TYPE_4__ {int rx_page_order; } ;
struct il_priv {TYPE_3__* pci_dev; TYPE_1__ hw_params; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * page; int /*<<< orphan*/  page_dma; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RX_FREE_BUFFERS ; 
 int RX_QUEUE_SIZE ; 
 int /*<<< orphan*/  __il_free_pages (struct il_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il3945_rx_queue_free(struct il_priv *il, struct il_rx_queue *rxq)
{
	int i;
	for (i = 0; i < RX_QUEUE_SIZE + RX_FREE_BUFFERS; i++) {
		if (rxq->pool[i].page != NULL) {
			pci_unmap_page(il->pci_dev, rxq->pool[i].page_dma,
				       PAGE_SIZE << il->hw_params.rx_page_order,
				       PCI_DMA_FROMDEVICE);
			__il_free_pages(il, rxq->pool[i].page);
			rxq->pool[i].page = NULL;
		}
	}

	dma_free_coherent(&il->pci_dev->dev, 4 * RX_QUEUE_SIZE, rxq->bd,
			  rxq->bd_dma);
	dma_free_coherent(&il->pci_dev->dev, sizeof(struct il_rb_status),
			  rxq->rb_stts, rxq->rb_stts_dma);
	rxq->bd = NULL;
	rxq->rb_stts = NULL;
}