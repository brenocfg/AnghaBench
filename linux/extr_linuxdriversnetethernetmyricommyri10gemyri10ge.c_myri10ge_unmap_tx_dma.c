#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct myri10ge_tx_buf {int mask; int req; TYPE_1__* info; } ;
struct myri10ge_priv {int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  bus ; 
 int /*<<< orphan*/  dma_unmap_addr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int dma_unmap_len (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_len_set (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void myri10ge_unmap_tx_dma(struct myri10ge_priv *mgp,
				  struct myri10ge_tx_buf *tx, int idx)
{
	unsigned int len;
	int last_idx;

	/* Free any DMA resources we've alloced and clear out the skb slot */
	last_idx = (idx + 1) & tx->mask;
	idx = tx->req & tx->mask;
	do {
		len = dma_unmap_len(&tx->info[idx], len);
		if (len) {
			if (tx->info[idx].skb != NULL)
				pci_unmap_single(mgp->pdev,
						 dma_unmap_addr(&tx->info[idx],
								bus), len,
						 PCI_DMA_TODEVICE);
			else
				pci_unmap_page(mgp->pdev,
					       dma_unmap_addr(&tx->info[idx],
							      bus), len,
					       PCI_DMA_TODEVICE);
			dma_unmap_len_set(&tx->info[idx], len, 0);
			tx->info[idx].skb = NULL;
		}
		idx = (idx + 1) & tx->mask;
	} while (idx != last_idx);
}