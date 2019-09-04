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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_start; scalar_t__ vm_end; int /*<<< orphan*/  vm_pgoff; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ io_remap_pfn_range (struct vm_area_struct*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int arc_hl_mmap(struct file *fp, struct vm_area_struct *vma)
{
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	if (io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot)) {
		pr_warn("Hostlink buffer mmap ERROR\n");
		return -EAGAIN;
	}
	return 0;
}