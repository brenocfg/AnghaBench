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
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPU3_PAGE_SIZE ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,scalar_t__) ; 
 int __imgu_mmu_map (struct imgu_mmu*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  call_if_imgu_is_powered (struct imgu_mmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,unsigned long*,size_t) ; 
 int /*<<< orphan*/  imgu_mmu_tlb_invalidate ; 
 struct imgu_mmu* to_imgu_mmu (struct imgu_mmu_info*) ; 

int imgu_mmu_map(struct imgu_mmu_info *info, unsigned long iova,
		 phys_addr_t paddr, size_t size)
{
	struct imgu_mmu *mmu = to_imgu_mmu(info);
	int ret = 0;

	/*
	 * both the virtual address and the physical one, as well as
	 * the size of the mapping, must be aligned (at least) to the
	 * size of the smallest page supported by the hardware
	 */
	if (!IS_ALIGNED(iova | paddr | size, IPU3_PAGE_SIZE)) {
		dev_err(mmu->dev, "unaligned: iova 0x%lx pa %pa size 0x%zx\n",
			iova, &paddr, size);
		return -EINVAL;
	}

	dev_dbg(mmu->dev, "map: iova 0x%lx pa %pa size 0x%zx\n",
		iova, &paddr, size);

	while (size) {
		dev_dbg(mmu->dev, "mapping: iova 0x%lx pa %pa\n", iova, &paddr);

		ret = __imgu_mmu_map(mmu, iova, paddr);
		if (ret)
			break;

		iova += IPU3_PAGE_SIZE;
		paddr += IPU3_PAGE_SIZE;
		size -= IPU3_PAGE_SIZE;
	}

	call_if_imgu_is_powered(mmu, imgu_mmu_tlb_invalidate);

	return ret;
}