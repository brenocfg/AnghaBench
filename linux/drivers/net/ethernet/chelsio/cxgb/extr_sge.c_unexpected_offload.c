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
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct freelQ_ce {struct sk_buff* skb; } ;
struct freelQ {size_t cidx; struct freelQ_ce* centries; } ;
struct adapter {int /*<<< orphan*/  name; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_len ; 
 int /*<<< orphan*/  dma_unmap_addr (struct freelQ_ce*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct freelQ_ce*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recycle_fl_buf (struct freelQ*,size_t) ; 

__attribute__((used)) static void unexpected_offload(struct adapter *adapter, struct freelQ *fl)
{
	struct freelQ_ce *ce = &fl->centries[fl->cidx];
	struct sk_buff *skb = ce->skb;

	pci_dma_sync_single_for_cpu(adapter->pdev, dma_unmap_addr(ce, dma_addr),
			    dma_unmap_len(ce, dma_len), PCI_DMA_FROMDEVICE);
	pr_err("%s: unexpected offload packet, cmd %u\n",
	       adapter->name, *skb->data);
	recycle_fl_buf(fl, fl->cidx);
}