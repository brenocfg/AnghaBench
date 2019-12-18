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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int PAGE_ALIGN (size_t) ; 
 int PAGE_SHIFT ; 
 int vm_map_pages (struct vm_area_struct*,struct page**,int) ; 

__attribute__((used)) static int __iommu_dma_mmap(struct page **pages, size_t size,
		struct vm_area_struct *vma)
{
	return vm_map_pages(vma, pages, PAGE_ALIGN(size) >> PAGE_SHIFT);
}