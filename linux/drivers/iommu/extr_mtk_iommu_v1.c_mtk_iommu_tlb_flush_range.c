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
typedef  scalar_t__ u32 ;
struct mtk_iommu_data {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long F_INVLD_EN0 ; 
 unsigned long F_INVLD_EN1 ; 
 unsigned long F_MMU_FAULT_VA_MSK ; 
 unsigned long F_MMU_INV_RANGE ; 
 scalar_t__ REG_MMU_CPE_DONE ; 
 scalar_t__ REG_MMU_INVALIDATE ; 
 scalar_t__ REG_MMU_INVLD_END_A ; 
 scalar_t__ REG_MMU_INVLD_START_A ; 
 scalar_t__ REG_MMU_INV_SEL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtk_iommu_tlb_flush_all (struct mtk_iommu_data*) ; 
 int readl_poll_timeout_atomic (scalar_t__,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static void mtk_iommu_tlb_flush_range(struct mtk_iommu_data *data,
				unsigned long iova, size_t size)
{
	int ret;
	u32 tmp;

	writel_relaxed(F_INVLD_EN1 | F_INVLD_EN0,
		data->base + REG_MMU_INV_SEL);
	writel_relaxed(iova & F_MMU_FAULT_VA_MSK,
		data->base + REG_MMU_INVLD_START_A);
	writel_relaxed((iova + size - 1) & F_MMU_FAULT_VA_MSK,
		data->base + REG_MMU_INVLD_END_A);
	writel_relaxed(F_MMU_INV_RANGE, data->base + REG_MMU_INVALIDATE);

	ret = readl_poll_timeout_atomic(data->base + REG_MMU_CPE_DONE,
				tmp, tmp != 0, 10, 100000);
	if (ret) {
		dev_warn(data->dev,
			 "Partial TLB flush timed out, falling back to full flush\n");
		mtk_iommu_tlb_flush_all(data);
	}
	/* Clear the CPE status */
	writel_relaxed(0, data->base + REG_MMU_CPE_DONE);
}