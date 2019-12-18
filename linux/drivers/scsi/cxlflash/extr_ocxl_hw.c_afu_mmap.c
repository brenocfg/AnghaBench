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
struct vm_area_struct {int vm_pgoff; int vm_flags; int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_page_prot; } ;
struct ocxlflash_context {int psn_size; } ;
struct file {struct ocxlflash_context* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int VM_IO ; 
 int VM_PFNMAP ; 
 int /*<<< orphan*/  ocxlflash_vmops ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static int afu_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct ocxlflash_context *ctx = file->private_data;

	if ((vma_pages(vma) + vma->vm_pgoff) >
	    (ctx->psn_size >> PAGE_SHIFT))
		return -EINVAL;

	vma->vm_flags |= VM_IO | VM_PFNMAP;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_ops = &ocxlflash_vmops;
	return 0;
}