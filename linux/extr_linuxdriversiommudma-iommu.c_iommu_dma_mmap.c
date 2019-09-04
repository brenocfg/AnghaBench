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
struct vm_area_struct {unsigned long vm_start; unsigned int vm_pgoff; unsigned long vm_end; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 unsigned int PAGE_ALIGN (size_t) ; 
 unsigned int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int vm_insert_page (struct vm_area_struct*,unsigned long,struct page*) ; 

int iommu_dma_mmap(struct page **pages, size_t size, struct vm_area_struct *vma)
{
	unsigned long uaddr = vma->vm_start;
	unsigned int i, count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	int ret = -ENXIO;

	for (i = vma->vm_pgoff; i < count && uaddr < vma->vm_end; i++) {
		ret = vm_insert_page(vma, uaddr, pages[i]);
		if (ret)
			break;
		uaddr += PAGE_SIZE;
	}
	return ret;
}