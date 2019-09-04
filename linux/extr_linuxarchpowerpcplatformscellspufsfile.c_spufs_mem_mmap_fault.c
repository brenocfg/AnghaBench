#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {unsigned long pgoff; int /*<<< orphan*/  address; struct vm_area_struct* vma; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; TYPE_1__* vm_file; } ;
struct TYPE_7__ {TYPE_2__* lscsa; } ;
struct spu_context {scalar_t__ state; TYPE_4__* spu; TYPE_3__ csa; } ;
struct TYPE_8__ {unsigned long local_store_phys; } ;
struct TYPE_6__ {scalar_t__ ls; } ;
struct TYPE_5__ {struct spu_context* private_data; } ;

/* Variables and functions */
 unsigned long LS_SIZE ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ SPU_STATE_SAVED ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  pgprot_cached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached_wc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 unsigned long vmalloc_to_pfn (scalar_t__) ; 
 int /*<<< orphan*/  vmf_insert_pfn (struct vm_area_struct*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static vm_fault_t
spufs_mem_mmap_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct spu_context *ctx	= vma->vm_file->private_data;
	unsigned long pfn, offset;
	vm_fault_t ret;

	offset = vmf->pgoff << PAGE_SHIFT;
	if (offset >= LS_SIZE)
		return VM_FAULT_SIGBUS;

	pr_debug("spufs_mem_mmap_fault address=0x%lx, offset=0x%lx\n",
			vmf->address, offset);

	if (spu_acquire(ctx))
		return VM_FAULT_NOPAGE;

	if (ctx->state == SPU_STATE_SAVED) {
		vma->vm_page_prot = pgprot_cached(vma->vm_page_prot);
		pfn = vmalloc_to_pfn(ctx->csa.lscsa->ls + offset);
	} else {
		vma->vm_page_prot = pgprot_noncached_wc(vma->vm_page_prot);
		pfn = (ctx->spu->local_store_phys + offset) >> PAGE_SHIFT;
	}
	ret = vmf_insert_pfn(vma, vmf->address, pfn);

	spu_release(ctx);

	return ret;
}