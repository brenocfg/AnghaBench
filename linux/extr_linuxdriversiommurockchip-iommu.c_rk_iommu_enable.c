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
struct rk_iommu_domain {int /*<<< orphan*/  dt_dma; } ;
struct rk_iommu {int num_mmu; int /*<<< orphan*/  clocks; int /*<<< orphan*/  num_clocks; int /*<<< orphan*/ * bases; struct iommu_domain* domain; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK_MMU_CMD_ZAP_CACHE ; 
 int /*<<< orphan*/  RK_MMU_DTE_ADDR ; 
 int /*<<< orphan*/  RK_MMU_INT_MASK ; 
 int /*<<< orphan*/  RK_MMU_IRQ_MASK ; 
 int /*<<< orphan*/  clk_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_base_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_disable_stall (struct rk_iommu*) ; 
 int rk_iommu_enable_paging (struct rk_iommu*) ; 
 int rk_iommu_enable_stall (struct rk_iommu*) ; 
 int rk_iommu_force_reset (struct rk_iommu*) ; 
 int /*<<< orphan*/  rk_iommu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rk_iommu_domain* to_rk_domain (struct iommu_domain*) ; 

__attribute__((used)) static int rk_iommu_enable(struct rk_iommu *iommu)
{
	struct iommu_domain *domain = iommu->domain;
	struct rk_iommu_domain *rk_domain = to_rk_domain(domain);
	int ret, i;

	ret = clk_bulk_enable(iommu->num_clocks, iommu->clocks);
	if (ret)
		return ret;

	ret = rk_iommu_enable_stall(iommu);
	if (ret)
		goto out_disable_clocks;

	ret = rk_iommu_force_reset(iommu);
	if (ret)
		goto out_disable_stall;

	for (i = 0; i < iommu->num_mmu; i++) {
		rk_iommu_write(iommu->bases[i], RK_MMU_DTE_ADDR,
			       rk_domain->dt_dma);
		rk_iommu_base_command(iommu->bases[i], RK_MMU_CMD_ZAP_CACHE);
		rk_iommu_write(iommu->bases[i], RK_MMU_INT_MASK, RK_MMU_IRQ_MASK);
	}

	ret = rk_iommu_enable_paging(iommu);

out_disable_stall:
	rk_iommu_disable_stall(iommu);
out_disable_clocks:
	clk_bulk_disable(iommu->num_clocks, iommu->clocks);
	return ret;
}