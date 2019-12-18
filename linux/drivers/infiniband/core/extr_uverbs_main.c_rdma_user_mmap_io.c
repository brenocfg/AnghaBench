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
struct vm_area_struct {int vm_flags; unsigned long vm_end; unsigned long vm_start; int /*<<< orphan*/  vm_page_prot; TYPE_1__* vm_file; } ;
struct rdma_umap_priv {int dummy; } ;
struct ib_uverbs_file {TYPE_2__* device; } ;
struct ib_ucontext {struct ib_uverbs_file* ufile; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_4__ {int /*<<< orphan*/  disassociate_srcu; } ;
struct TYPE_3__ {struct ib_uverbs_file* private_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int VM_SHARED ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ io_remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rdma_umap_priv*) ; 
 struct rdma_umap_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_umap_priv_init (struct rdma_umap_priv*,struct vm_area_struct*) ; 

int rdma_user_mmap_io(struct ib_ucontext *ucontext, struct vm_area_struct *vma,
		      unsigned long pfn, unsigned long size, pgprot_t prot)
{
	struct ib_uverbs_file *ufile = ucontext->ufile;
	struct rdma_umap_priv *priv;

	if (!(vma->vm_flags & VM_SHARED))
		return -EINVAL;

	if (vma->vm_end - vma->vm_start != size)
		return -EINVAL;

	/* Driver is using this wrong, must be called by ib_uverbs_mmap */
	if (WARN_ON(!vma->vm_file ||
		    vma->vm_file->private_data != ufile))
		return -EINVAL;
	lockdep_assert_held(&ufile->device->disassociate_srcu);

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	vma->vm_page_prot = prot;
	if (io_remap_pfn_range(vma, vma->vm_start, pfn, size, prot)) {
		kfree(priv);
		return -EAGAIN;
	}

	rdma_umap_priv_init(priv, vma);
	return 0;
}