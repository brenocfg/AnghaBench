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
typedef  scalar_t__ u64 ;
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; unsigned int vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct vfio_platform_region {scalar_t__ size; scalar_t__ addr; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned int VFIO_PLATFORM_OFFSET_SHIFT ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int remap_pfn_range (struct vm_area_struct*,scalar_t__,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfio_platform_mmap_mmio(struct vfio_platform_region region,
				   struct vm_area_struct *vma)
{
	u64 req_len, pgoff, req_start;

	req_len = vma->vm_end - vma->vm_start;
	pgoff = vma->vm_pgoff &
		((1U << (VFIO_PLATFORM_OFFSET_SHIFT - PAGE_SHIFT)) - 1);
	req_start = pgoff << PAGE_SHIFT;

	if (region.size < PAGE_SIZE || req_start + req_len > region.size)
		return -EINVAL;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_pgoff = (region.addr >> PAGE_SHIFT) + pgoff;

	return remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
			       req_len, vma->vm_page_prot);
}