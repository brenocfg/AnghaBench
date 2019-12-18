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
typedef  scalar_t__ u16 ;
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; unsigned long vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct fb_info {int dummy; } ;
struct TYPE_2__ {scalar_t__* cpu; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long TILE_MASK ; 
 unsigned long TILE_SHIFT ; 
 unsigned long TILE_SIZE ; 
 unsigned long gbe_mem_size ; 
 TYPE_1__ gbe_tiles ; 
 int /*<<< orphan*/  pgprot_fb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_val (int /*<<< orphan*/ ) ; 
 scalar_t__ remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gbefb_mmap(struct fb_info *info,
			struct vm_area_struct *vma)
{
	unsigned long size = vma->vm_end - vma->vm_start;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long addr;
	unsigned long phys_addr, phys_size;
	u16 *tile;

	/* check range */
	if (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
		return -EINVAL;
	if (size > gbe_mem_size)
		return -EINVAL;
	if (offset > gbe_mem_size - size)
		return -EINVAL;

	/* remap using the fastest write-through mode on architecture */
	/* try not polluting the cache when possible */
#ifdef CONFIG_MIPS
	pgprot_val(vma->vm_page_prot) =
		pgprot_fb(pgprot_val(vma->vm_page_prot));
#endif
	/* VM_IO | VM_DONTEXPAND | VM_DONTDUMP are set by remap_pfn_range() */

	/* look for the starting tile */
	tile = &gbe_tiles.cpu[offset >> TILE_SHIFT];
	addr = vma->vm_start;
	offset &= TILE_MASK;

	/* remap each tile separately */
	do {
		phys_addr = (((unsigned long) (*tile)) << TILE_SHIFT) + offset;
		if ((offset + size) < TILE_SIZE)
			phys_size = size;
		else
			phys_size = TILE_SIZE - offset;

		if (remap_pfn_range(vma, addr, phys_addr >> PAGE_SHIFT,
						phys_size, vma->vm_page_prot))
			return -EAGAIN;

		offset = 0;
		size -= phys_size;
		addr += phys_size;
		tile++;
	} while (size);

	return 0;
}