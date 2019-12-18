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
struct iommu_iotlb_gather {int dummy; } ;
struct io_pgtable_cfg {int dummy; } ;
struct TYPE_2__ {struct io_pgtable_cfg cfg; } ;
struct arm_lpae_io_pgtable {TYPE_1__ iop; } ;
typedef  int /*<<< orphan*/  pte ;
typedef  size_t phys_addr_t ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 size_t ARM_LPAE_BLOCK_SIZE (int,struct arm_lpae_io_pgtable*) ; 
 size_t ARM_LPAE_GRANULE (struct arm_lpae_io_pgtable*) ; 
 int ARM_LPAE_LVL_IDX (unsigned long,int,struct arm_lpae_io_pgtable*) ; 
 int ARM_LPAE_MAX_LEVELS ; 
 scalar_t__ ARM_LPAE_PTE_TYPE_TABLE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/ * __arm_lpae_alloc_pages (size_t,int /*<<< orphan*/ ,struct io_pgtable_cfg*) ; 
 int /*<<< orphan*/  __arm_lpae_free_pages (int /*<<< orphan*/ *,size_t,struct io_pgtable_cfg*) ; 
 int /*<<< orphan*/  __arm_lpae_init_pte (struct arm_lpae_io_pgtable*,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 size_t __arm_lpae_unmap (struct arm_lpae_io_pgtable*,struct iommu_iotlb_gather*,unsigned long,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arm_lpae_install_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct io_pgtable_cfg*) ; 
 int /*<<< orphan*/  io_pgtable_tlb_add_page (TYPE_1__*,struct iommu_iotlb_gather*,unsigned long,size_t) ; 
 int /*<<< orphan*/ * iopte_deref (int /*<<< orphan*/ ,struct arm_lpae_io_pgtable*) ; 
 int /*<<< orphan*/  iopte_prot (int /*<<< orphan*/ ) ; 
 size_t iopte_to_paddr (int /*<<< orphan*/ ,struct arm_lpae_io_pgtable*) ; 
 scalar_t__ iopte_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t arm_lpae_split_blk_unmap(struct arm_lpae_io_pgtable *data,
				       struct iommu_iotlb_gather *gather,
				       unsigned long iova, size_t size,
				       arm_lpae_iopte blk_pte, int lvl,
				       arm_lpae_iopte *ptep)
{
	struct io_pgtable_cfg *cfg = &data->iop.cfg;
	arm_lpae_iopte pte, *tablep;
	phys_addr_t blk_paddr;
	size_t tablesz = ARM_LPAE_GRANULE(data);
	size_t split_sz = ARM_LPAE_BLOCK_SIZE(lvl, data);
	int i, unmap_idx = -1;

	if (WARN_ON(lvl == ARM_LPAE_MAX_LEVELS))
		return 0;

	tablep = __arm_lpae_alloc_pages(tablesz, GFP_ATOMIC, cfg);
	if (!tablep)
		return 0; /* Bytes unmapped */

	if (size == split_sz)
		unmap_idx = ARM_LPAE_LVL_IDX(iova, lvl, data);

	blk_paddr = iopte_to_paddr(blk_pte, data);
	pte = iopte_prot(blk_pte);

	for (i = 0; i < tablesz / sizeof(pte); i++, blk_paddr += split_sz) {
		/* Unmap! */
		if (i == unmap_idx)
			continue;

		__arm_lpae_init_pte(data, blk_paddr, pte, lvl, &tablep[i]);
	}

	pte = arm_lpae_install_table(tablep, ptep, blk_pte, cfg);
	if (pte != blk_pte) {
		__arm_lpae_free_pages(tablep, tablesz, cfg);
		/*
		 * We may race against someone unmapping another part of this
		 * block, but anything else is invalid. We can't misinterpret
		 * a page entry here since we're never at the last level.
		 */
		if (iopte_type(pte, lvl - 1) != ARM_LPAE_PTE_TYPE_TABLE)
			return 0;

		tablep = iopte_deref(pte, data);
	} else if (unmap_idx >= 0) {
		io_pgtable_tlb_add_page(&data->iop, gather, iova, size);
		return size;
	}

	return __arm_lpae_unmap(data, gather, iova, size, lvl, tablep);
}