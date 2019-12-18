#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct tid_user_buf {scalar_t__ vaddr; struct page** pages; } ;
struct TYPE_5__ {unsigned int len; scalar_t__ addr; } ;
struct tid_rb_node {unsigned int npages; int freed; int /*<<< orphan*/  phys; TYPE_1__ mmu; int /*<<< orphan*/  rcventry; int /*<<< orphan*/  pages; struct tid_group* grp; int /*<<< orphan*/  dma_addr; } ;
struct tid_group {int dummy; } ;
struct page {int dummy; } ;
struct hfi1_filedata {int /*<<< orphan*/  subctxt; int /*<<< orphan*/  handler; struct hfi1_ctxtdata* uctxt; } ;
struct hfi1_devdata {TYPE_2__* pcidev; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  ctxt; struct hfi1_devdata* dd; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PT_EXPECTED ; 
 int /*<<< orphan*/  TID ; 
 int /*<<< orphan*/  __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_cdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int hfi1_mmu_rb_insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  hfi1_put_tid (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ilog2 (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct tid_rb_node*) ; 
 struct tid_rb_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct page**,int) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 int /*<<< orphan*/  pci_map_single (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int tid_rb_insert (struct hfi1_filedata*,TYPE_1__*) ; 
 int /*<<< orphan*/  trace_hfi1_exp_tid_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_rcvarray_entry(struct hfi1_filedata *fd,
			      struct tid_user_buf *tbuf,
			      u32 rcventry, struct tid_group *grp,
			      u16 pageidx, unsigned int npages)
{
	int ret;
	struct hfi1_ctxtdata *uctxt = fd->uctxt;
	struct tid_rb_node *node;
	struct hfi1_devdata *dd = uctxt->dd;
	dma_addr_t phys;
	struct page **pages = tbuf->pages + pageidx;

	/*
	 * Allocate the node first so we can handle a potential
	 * failure before we've programmed anything.
	 */
	node = kzalloc(sizeof(*node) + (sizeof(struct page *) * npages),
		       GFP_KERNEL);
	if (!node)
		return -ENOMEM;

	phys = pci_map_single(dd->pcidev,
			      __va(page_to_phys(pages[0])),
			      npages * PAGE_SIZE, PCI_DMA_FROMDEVICE);
	if (dma_mapping_error(&dd->pcidev->dev, phys)) {
		dd_dev_err(dd, "Failed to DMA map Exp Rcv pages 0x%llx\n",
			   phys);
		kfree(node);
		return -EFAULT;
	}

	node->mmu.addr = tbuf->vaddr + (pageidx * PAGE_SIZE);
	node->mmu.len = npages * PAGE_SIZE;
	node->phys = page_to_phys(pages[0]);
	node->npages = npages;
	node->rcventry = rcventry;
	node->dma_addr = phys;
	node->grp = grp;
	node->freed = false;
	memcpy(node->pages, pages, sizeof(struct page *) * npages);

	if (!fd->handler)
		ret = tid_rb_insert(fd, &node->mmu);
	else
		ret = hfi1_mmu_rb_insert(fd->handler, &node->mmu);

	if (ret) {
		hfi1_cdbg(TID, "Failed to insert RB node %u 0x%lx, 0x%lx %d",
			  node->rcventry, node->mmu.addr, node->phys, ret);
		pci_unmap_single(dd->pcidev, phys, npages * PAGE_SIZE,
				 PCI_DMA_FROMDEVICE);
		kfree(node);
		return -EFAULT;
	}
	hfi1_put_tid(dd, rcventry, PT_EXPECTED, phys, ilog2(npages) + 1);
	trace_hfi1_exp_tid_reg(uctxt->ctxt, fd->subctxt, rcventry, npages,
			       node->mmu.addr, node->phys, phys);
	return 0;
}