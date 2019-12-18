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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int gfp_mask; scalar_t__ page; int /*<<< orphan*/  address; TYPE_2__* vma; } ;
struct rdma_umap_priv {int dummy; } ;
struct ib_uverbs_file {int /*<<< orphan*/  umap_lock; scalar_t__ disassociate_page; } ;
struct TYPE_4__ {int vm_flags; struct rdma_umap_priv* vm_private_data; TYPE_1__* vm_file; } ;
struct TYPE_3__ {struct ib_uverbs_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int VM_MAYWRITE ; 
 int VM_WRITE ; 
 scalar_t__ ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int __GFP_ZERO ; 
 scalar_t__ alloc_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_fault_t rdma_umap_fault(struct vm_fault *vmf)
{
	struct ib_uverbs_file *ufile = vmf->vma->vm_file->private_data;
	struct rdma_umap_priv *priv = vmf->vma->vm_private_data;
	vm_fault_t ret = 0;

	if (!priv)
		return VM_FAULT_SIGBUS;

	/* Read only pages can just use the system zero page. */
	if (!(vmf->vma->vm_flags & (VM_WRITE | VM_MAYWRITE))) {
		vmf->page = ZERO_PAGE(vmf->address);
		get_page(vmf->page);
		return 0;
	}

	mutex_lock(&ufile->umap_lock);
	if (!ufile->disassociate_page)
		ufile->disassociate_page =
			alloc_pages(vmf->gfp_mask | __GFP_ZERO, 0);

	if (ufile->disassociate_page) {
		/*
		 * This VMA is forced to always be shared so this doesn't have
		 * to worry about COW.
		 */
		vmf->page = ufile->disassociate_page;
		get_page(vmf->page);
	} else {
		ret = VM_FAULT_SIGBUS;
	}
	mutex_unlock(&ufile->umap_lock);

	return ret;
}