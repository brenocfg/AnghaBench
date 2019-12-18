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
struct vm_area_struct {int vm_pgoff; int vm_flags; } ;
struct ocxl_context {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int VM_EXEC ; 
 int VM_MAYEXEC ; 
 int VM_MAYREAD ; 
 int VM_READ ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  ocxl_afu_irq_get_addr (struct ocxl_context*,int) ; 
 int ocxl_irq_offset_to_id (struct ocxl_context*,int) ; 
 int vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static int check_mmap_afu_irq(struct ocxl_context *ctx,
			struct vm_area_struct *vma)
{
	int irq_id = ocxl_irq_offset_to_id(ctx, vma->vm_pgoff << PAGE_SHIFT);

	/* only one page */
	if (vma_pages(vma) != 1)
		return -EINVAL;

	/* check offset validty */
	if (!ocxl_afu_irq_get_addr(ctx, irq_id))
		return -EINVAL;

	/*
	 * trigger page should only be accessible in write mode.
	 *
	 * It's a bit theoretical, as a page mmaped with only
	 * PROT_WRITE is currently readable, but it doesn't hurt.
	 */
	if ((vma->vm_flags & VM_READ) || (vma->vm_flags & VM_EXEC) ||
		!(vma->vm_flags & VM_WRITE))
		return -EINVAL;
	vma->vm_flags &= ~(VM_MAYREAD | VM_MAYEXEC);
	return 0;
}