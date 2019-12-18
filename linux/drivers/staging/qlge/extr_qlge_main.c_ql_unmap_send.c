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
struct tx_ring_desc {int /*<<< orphan*/ * map; } ;
struct ql_adapter {int /*<<< orphan*/  pdev; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dma_unmap_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_done ; 

__attribute__((used)) static void ql_unmap_send(struct ql_adapter *qdev,
			  struct tx_ring_desc *tx_ring_desc, int mapped)
{
	int i;
	for (i = 0; i < mapped; i++) {
		if (i == 0 || (i == 7 && mapped > 7)) {
			/*
			 * Unmap the skb->data area, or the
			 * external sglist (AKA the Outbound
			 * Address List (OAL)).
			 * If its the zeroeth element, then it's
			 * the skb->data area.  If it's the 7th
			 * element and there is more than 6 frags,
			 * then its an OAL.
			 */
			if (i == 7) {
				netif_printk(qdev, tx_done, KERN_DEBUG,
					     qdev->ndev,
					     "unmapping OAL area.\n");
			}
			pci_unmap_single(qdev->pdev,
					 dma_unmap_addr(&tx_ring_desc->map[i],
							mapaddr),
					 dma_unmap_len(&tx_ring_desc->map[i],
						       maplen),
					 PCI_DMA_TODEVICE);
		} else {
			netif_printk(qdev, tx_done, KERN_DEBUG, qdev->ndev,
				     "unmapping frag %d.\n", i);
			pci_unmap_page(qdev->pdev,
				       dma_unmap_addr(&tx_ring_desc->map[i],
						      mapaddr),
				       dma_unmap_len(&tx_ring_desc->map[i],
						     maplen), PCI_DMA_TODEVICE);
		}
	}

}