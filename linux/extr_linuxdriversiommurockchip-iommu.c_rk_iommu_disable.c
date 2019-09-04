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
struct rk_iommu {int num_mmu; int /*<<< orphan*/  clocks; int /*<<< orphan*/  num_clocks; int /*<<< orphan*/ * bases; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK_MMU_DTE_ADDR ; 
 int /*<<< orphan*/  RK_MMU_INT_MASK ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_disable_paging (struct rk_iommu*) ; 
 int /*<<< orphan*/  rk_iommu_disable_stall (struct rk_iommu*) ; 
 int /*<<< orphan*/  rk_iommu_enable_stall (struct rk_iommu*) ; 
 int /*<<< orphan*/  rk_iommu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rk_iommu_disable(struct rk_iommu *iommu)
{
	int i;

	/* Ignore error while disabling, just keep going */
	WARN_ON(clk_bulk_enable(iommu->num_clocks, iommu->clocks));
	rk_iommu_enable_stall(iommu);
	rk_iommu_disable_paging(iommu);
	for (i = 0; i < iommu->num_mmu; i++) {
		rk_iommu_write(iommu->bases[i], RK_MMU_INT_MASK, 0);
		rk_iommu_write(iommu->bases[i], RK_MMU_DTE_ADDR, 0);
	}
	rk_iommu_disable_stall(iommu);
	clk_bulk_disable(iommu->num_clocks, iommu->clocks);
}