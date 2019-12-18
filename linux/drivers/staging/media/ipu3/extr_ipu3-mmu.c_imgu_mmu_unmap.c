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
struct imgu_mmu_info {int dummy; } ;
struct imgu_mmu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  IPU3_PAGE_SIZE ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 size_t __imgu_mmu_unmap (struct imgu_mmu*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_if_imgu_is_powered (struct imgu_mmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,size_t) ; 
 int /*<<< orphan*/  imgu_mmu_tlb_invalidate ; 
 struct imgu_mmu* to_imgu_mmu (struct imgu_mmu_info*) ; 

size_t imgu_mmu_unmap(struct imgu_mmu_info *info, unsigned long iova,
		      size_t size)
{
	struct imgu_mmu *mmu = to_imgu_mmu(info);
	size_t unmapped_page, unmapped = 0;

	/*
	 * The virtual address, as well as the size of the mapping, must be
	 * aligned (at least) to the size of the smallest page supported
	 * by the hardware
	 */
	if (!IS_ALIGNED(iova | size, IPU3_PAGE_SIZE)) {
		dev_err(mmu->dev, "unaligned: iova 0x%lx size 0x%zx\n",
			iova, size);
		return -EINVAL;
	}

	dev_dbg(mmu->dev, "unmap this: iova 0x%lx size 0x%zx\n", iova, size);

	/*
	 * Keep iterating until we either unmap 'size' bytes (or more)
	 * or we hit an area that isn't mapped.
	 */
	while (unmapped < size) {
		unmapped_page = __imgu_mmu_unmap(mmu, iova, IPU3_PAGE_SIZE);
		if (!unmapped_page)
			break;

		dev_dbg(mmu->dev, "unmapped: iova 0x%lx size 0x%zx\n",
			iova, unmapped_page);

		iova += unmapped_page;
		unmapped += unmapped_page;
	}

	call_if_imgu_is_powered(mmu, imgu_mmu_tlb_invalidate);

	return unmapped;
}