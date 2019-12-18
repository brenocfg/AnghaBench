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
struct sge {TYPE_1__* adapter; } ;
struct pci_dev {int dummy; } ;
struct cmdQ_ce {scalar_t__ skb; } ;
struct cmdQ {unsigned int cidx; unsigned int in_use; int sop; unsigned int size; struct cmdQ_ce* centries; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_len ; 
 int /*<<< orphan*/  dma_unmap_addr (struct cmdQ_ce*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct cmdQ_ce*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_cmdQ_buffers(struct sge *sge, struct cmdQ *q, unsigned int n)
{
	struct cmdQ_ce *ce;
	struct pci_dev *pdev = sge->adapter->pdev;
	unsigned int cidx = q->cidx;

	q->in_use -= n;
	ce = &q->centries[cidx];
	while (n--) {
		if (likely(dma_unmap_len(ce, dma_len))) {
			pci_unmap_single(pdev, dma_unmap_addr(ce, dma_addr),
					 dma_unmap_len(ce, dma_len),
					 PCI_DMA_TODEVICE);
			if (q->sop)
				q->sop = 0;
		}
		if (ce->skb) {
			dev_kfree_skb_any(ce->skb);
			q->sop = 1;
		}
		ce++;
		if (++cidx == q->size) {
			cidx = 0;
			ce = q->centries;
		}
	}
	q->cidx = cidx;
}