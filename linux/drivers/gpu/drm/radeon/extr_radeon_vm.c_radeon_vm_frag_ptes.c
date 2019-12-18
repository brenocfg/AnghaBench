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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct radeon_ib {int dummy; } ;
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 scalar_t__ CHIP_ARUBA ; 
 scalar_t__ CHIP_CAYMAN ; 
 int R600_PTE_FRAG_256KB ; 
 int R600_PTE_FRAG_64KB ; 
 int R600_PTE_SYSTEM ; 
 int R600_PTE_VALID ; 
 unsigned int RADEON_GPU_PAGE_SIZE ; 
 int /*<<< orphan*/  radeon_vm_set_pages (struct radeon_device*,struct radeon_ib*,int,int,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void radeon_vm_frag_ptes(struct radeon_device *rdev,
				struct radeon_ib *ib,
				uint64_t pe_start, uint64_t pe_end,
				uint64_t addr, uint32_t flags)
{
	/**
	 * The MC L1 TLB supports variable sized pages, based on a fragment
	 * field in the PTE. When this field is set to a non-zero value, page
	 * granularity is increased from 4KB to (1 << (12 + frag)). The PTE
	 * flags are considered valid for all PTEs within the fragment range
	 * and corresponding mappings are assumed to be physically contiguous.
	 *
	 * The L1 TLB can store a single PTE for the whole fragment,
	 * significantly increasing the space available for translation
	 * caching. This leads to large improvements in throughput when the
	 * TLB is under pressure.
	 *
	 * The L2 TLB distributes small and large fragments into two
	 * asymmetric partitions. The large fragment cache is significantly
	 * larger. Thus, we try to use large fragments wherever possible.
	 * Userspace can support this by aligning virtual base address and
	 * allocation size to the fragment size.
	 */

	/* NI is optimized for 256KB fragments, SI and newer for 64KB */
	uint64_t frag_flags = ((rdev->family == CHIP_CAYMAN) ||
			       (rdev->family == CHIP_ARUBA)) ?
			R600_PTE_FRAG_256KB : R600_PTE_FRAG_64KB;
	uint64_t frag_align = ((rdev->family == CHIP_CAYMAN) ||
			       (rdev->family == CHIP_ARUBA)) ? 0x200 : 0x80;

	uint64_t frag_start = ALIGN(pe_start, frag_align);
	uint64_t frag_end = pe_end & ~(frag_align - 1);

	unsigned count;

	/* system pages are non continuously */
	if ((flags & R600_PTE_SYSTEM) || !(flags & R600_PTE_VALID) ||
	    (frag_start >= frag_end)) {

		count = (pe_end - pe_start) / 8;
		radeon_vm_set_pages(rdev, ib, pe_start, addr, count,
				    RADEON_GPU_PAGE_SIZE, flags);
		return;
	}

	/* handle the 4K area at the beginning */
	if (pe_start != frag_start) {
		count = (frag_start - pe_start) / 8;
		radeon_vm_set_pages(rdev, ib, pe_start, addr, count,
				    RADEON_GPU_PAGE_SIZE, flags);
		addr += RADEON_GPU_PAGE_SIZE * count;
	}

	/* handle the area in the middle */
	count = (frag_end - frag_start) / 8;
	radeon_vm_set_pages(rdev, ib, frag_start, addr, count,
			    RADEON_GPU_PAGE_SIZE, flags | frag_flags);

	/* handle the 4K area at the end */
	if (frag_end != pe_end) {
		addr += RADEON_GPU_PAGE_SIZE * count;
		count = (pe_end - frag_end) / 8;
		radeon_vm_set_pages(rdev, ib, frag_end, addr, count,
				    RADEON_GPU_PAGE_SIZE, flags);
	}
}