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
typedef  int /*<<< orphan*/  u64 ;
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 unsigned long vma_kernel_pagesize (struct vm_area_struct*) ; 

__attribute__((used)) static int get_vma_info(struct mm_struct *mm, u64 addr,
			u64 *vma_start, u64 *vma_end,
			unsigned long *page_size)
{
	struct vm_area_struct *vma = NULL;
	int rc = 0;

	down_read(&mm->mmap_sem);

	vma = find_vma(mm, addr);
	if (!vma) {
		rc = -EFAULT;
		goto out;
	}
	*page_size = vma_kernel_pagesize(vma);
	*vma_start = vma->vm_start;
	*vma_end = vma->vm_end;
out:
	up_read(&mm->mmap_sem);
	return rc;
}