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
struct vm_area_struct {scalar_t__ vm_pgoff; int vm_end; int vm_start; int /*<<< orphan*/  vm_page_prot; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int mmapper_size ; 
 int p_buf ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmapper_mmap(struct file *file, struct vm_area_struct *vma)
{
	int ret = -EINVAL;
	int size;

	if (vma->vm_pgoff != 0)
		goto out;

	size = vma->vm_end - vma->vm_start;
	if (size > mmapper_size)
		return -EFAULT;

	/*
	 * XXX A comment above remap_pfn_range says it should only be
	 * called when the mm semaphore is held
	 */
	if (remap_pfn_range(vma, vma->vm_start, p_buf >> PAGE_SHIFT, size,
			    vma->vm_page_prot))
		goto out;
	ret = 0;
out:
	return ret;
}