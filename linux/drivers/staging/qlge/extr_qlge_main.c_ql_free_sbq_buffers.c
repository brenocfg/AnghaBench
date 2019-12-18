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
struct rx_ring {int sbq_len; struct bq_desc* sbq; } ;
struct ql_adapter {int /*<<< orphan*/  pdev; int /*<<< orphan*/  ndev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * skb; } ;
struct bq_desc {TYPE_1__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct bq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct bq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql_free_sbq_buffers(struct ql_adapter *qdev, struct rx_ring *rx_ring)
{
	int i;
	struct bq_desc *sbq_desc;

	for (i = 0; i < rx_ring->sbq_len; i++) {
		sbq_desc = &rx_ring->sbq[i];
		if (sbq_desc == NULL) {
			netif_err(qdev, ifup, qdev->ndev,
				  "sbq_desc %d is NULL.\n", i);
			return;
		}
		if (sbq_desc->p.skb) {
			pci_unmap_single(qdev->pdev,
					 dma_unmap_addr(sbq_desc, mapaddr),
					 dma_unmap_len(sbq_desc, maplen),
					 PCI_DMA_FROMDEVICE);
			dev_kfree_skb(sbq_desc->p.skb);
			sbq_desc->p.skb = NULL;
		}
	}
}