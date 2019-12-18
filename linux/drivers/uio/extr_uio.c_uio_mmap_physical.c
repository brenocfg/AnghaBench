#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/ * vm_ops; struct uio_device* vm_private_data; } ;
struct uio_mem {int addr; scalar_t__ size; scalar_t__ memtype; } ;
struct uio_device {TYPE_1__* info; } ;
struct TYPE_2__ {struct uio_mem* mem; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 scalar_t__ UIO_MEM_PHYS ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int remap_pfn_range (struct vm_area_struct*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int uio_find_mem_index (struct vm_area_struct*) ; 
 int /*<<< orphan*/  uio_physical_vm_ops ; 

__attribute__((used)) static int uio_mmap_physical(struct vm_area_struct *vma)
{
	struct uio_device *idev = vma->vm_private_data;
	int mi = uio_find_mem_index(vma);
	struct uio_mem *mem;

	if (mi < 0)
		return -EINVAL;
	mem = idev->info->mem + mi;

	if (mem->addr & ~PAGE_MASK)
		return -ENODEV;
	if (vma->vm_end - vma->vm_start > mem->size)
		return -EINVAL;

	vma->vm_ops = &uio_physical_vm_ops;
	if (idev->info->mem[mi].memtype == UIO_MEM_PHYS)
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	/*
	 * We cannot use the vm_iomap_memory() helper here,
	 * because vma->vm_pgoff is the map index we looked
	 * up above in uio_find_mem_index(), rather than an
	 * actual page offset into the mmap.
	 *
	 * So we just do the physical mmap without a page
	 * offset.
	 */
	return remap_pfn_range(vma,
			       vma->vm_start,
			       mem->addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}