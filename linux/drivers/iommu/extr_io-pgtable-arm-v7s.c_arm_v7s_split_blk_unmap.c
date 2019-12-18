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
struct arm_v7s_io_pgtable {TYPE_1__ iop; } ;
typedef  scalar_t__ arm_v7s_iopte ;

/* Variables and functions */
 int ARM_V7S_LVL_IDX (unsigned long,int) ; 
 size_t ARM_V7S_LVL_SHIFT (int) ; 
 int ARM_V7S_PTES_PER_LVL (int) ; 
 int /*<<< orphan*/  ARM_V7S_PTE_IS_TABLE (scalar_t__,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__* __arm_v7s_alloc_table (int,int /*<<< orphan*/ ,struct arm_v7s_io_pgtable*) ; 
 int /*<<< orphan*/  __arm_v7s_free_table (scalar_t__*,int,struct arm_v7s_io_pgtable*) ; 
 int /*<<< orphan*/  __arm_v7s_set_pte (scalar_t__*,scalar_t__,int,struct io_pgtable_cfg*) ; 
 size_t __arm_v7s_unmap (struct arm_v7s_io_pgtable*,struct iommu_iotlb_gather*,unsigned long,size_t,int,scalar_t__*) ; 
 scalar_t__ arm_v7s_install_table (scalar_t__*,scalar_t__*,scalar_t__,struct io_pgtable_cfg*) ; 
 scalar_t__ arm_v7s_prot_to_pte (int /*<<< orphan*/ ,int,struct io_pgtable_cfg*) ; 
 scalar_t__ arm_v7s_pte_to_cont (scalar_t__,int) ; 
 int /*<<< orphan*/  arm_v7s_pte_to_prot (scalar_t__,int) ; 
 int /*<<< orphan*/  io_pgtable_tlb_add_page (TYPE_1__*,struct iommu_iotlb_gather*,unsigned long,size_t) ; 
 scalar_t__* iopte_deref (scalar_t__,int,struct arm_v7s_io_pgtable*) ; 

__attribute__((used)) static size_t arm_v7s_split_blk_unmap(struct arm_v7s_io_pgtable *data,
				      struct iommu_iotlb_gather *gather,
				      unsigned long iova, size_t size,
				      arm_v7s_iopte blk_pte,
				      arm_v7s_iopte *ptep)
{
	struct io_pgtable_cfg *cfg = &data->iop.cfg;
	arm_v7s_iopte pte, *tablep;
	int i, unmap_idx, num_entries, num_ptes;

	tablep = __arm_v7s_alloc_table(2, GFP_ATOMIC, data);
	if (!tablep)
		return 0; /* Bytes unmapped */

	num_ptes = ARM_V7S_PTES_PER_LVL(2);
	num_entries = size >> ARM_V7S_LVL_SHIFT(2);
	unmap_idx = ARM_V7S_LVL_IDX(iova, 2);

	pte = arm_v7s_prot_to_pte(arm_v7s_pte_to_prot(blk_pte, 1), 2, cfg);
	if (num_entries > 1)
		pte = arm_v7s_pte_to_cont(pte, 2);

	for (i = 0; i < num_ptes; i += num_entries, pte += size) {
		/* Unmap! */
		if (i == unmap_idx)
			continue;

		__arm_v7s_set_pte(&tablep[i], pte, num_entries, cfg);
	}

	pte = arm_v7s_install_table(tablep, ptep, blk_pte, cfg);
	if (pte != blk_pte) {
		__arm_v7s_free_table(tablep, 2, data);

		if (!ARM_V7S_PTE_IS_TABLE(pte, 1))
			return 0;

		tablep = iopte_deref(pte, 1, data);
		return __arm_v7s_unmap(data, gather, iova, size, 2, tablep);
	}

	io_pgtable_tlb_add_page(&data->iop, gather, iova, size);
	return size;
}