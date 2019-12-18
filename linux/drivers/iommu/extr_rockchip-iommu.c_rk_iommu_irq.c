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
typedef  int u32 ;
struct rk_iommu {int num_mmu; int /*<<< orphan*/  dev; int /*<<< orphan*/  clocks; int /*<<< orphan*/  num_clocks; int /*<<< orphan*/ * bases; scalar_t__ domain; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int IOMMU_FAULT_READ ; 
 int IOMMU_FAULT_WRITE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  RK_MMU_CMD_PAGE_FAULT_DONE ; 
 int /*<<< orphan*/  RK_MMU_CMD_ZAP_CACHE ; 
 int /*<<< orphan*/  RK_MMU_INT_CLEAR ; 
 int /*<<< orphan*/  RK_MMU_INT_STATUS ; 
 int RK_MMU_IRQ_BUS_ERROR ; 
 int RK_MMU_IRQ_MASK ; 
 int RK_MMU_IRQ_PAGE_FAULT ; 
 int /*<<< orphan*/  RK_MMU_PAGE_FAULT_ADDR ; 
 int /*<<< orphan*/  RK_MMU_STATUS ; 
 int RK_MMU_STATUS_PAGE_FAULT_IS_WRITE ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clk_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  log_iova (struct rk_iommu*,int,void*) ; 
 int pm_runtime_get_if_in_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_iommu_fault (scalar_t__,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  rk_iommu_base_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* rk_iommu_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t rk_iommu_irq(int irq, void *dev_id)
{
	struct rk_iommu *iommu = dev_id;
	u32 status;
	u32 int_status;
	dma_addr_t iova;
	irqreturn_t ret = IRQ_NONE;
	int i, err;

	err = pm_runtime_get_if_in_use(iommu->dev);
	if (WARN_ON_ONCE(err <= 0))
		return ret;

	if (WARN_ON(clk_bulk_enable(iommu->num_clocks, iommu->clocks)))
		goto out;

	for (i = 0; i < iommu->num_mmu; i++) {
		int_status = rk_iommu_read(iommu->bases[i], RK_MMU_INT_STATUS);
		if (int_status == 0)
			continue;

		ret = IRQ_HANDLED;
		iova = rk_iommu_read(iommu->bases[i], RK_MMU_PAGE_FAULT_ADDR);

		if (int_status & RK_MMU_IRQ_PAGE_FAULT) {
			int flags;

			status = rk_iommu_read(iommu->bases[i], RK_MMU_STATUS);
			flags = (status & RK_MMU_STATUS_PAGE_FAULT_IS_WRITE) ?
					IOMMU_FAULT_WRITE : IOMMU_FAULT_READ;

			dev_err(iommu->dev, "Page fault at %pad of type %s\n",
				&iova,
				(flags == IOMMU_FAULT_WRITE) ? "write" : "read");

			log_iova(iommu, i, iova);

			/*
			 * Report page fault to any installed handlers.
			 * Ignore the return code, though, since we always zap cache
			 * and clear the page fault anyway.
			 */
			if (iommu->domain)
				report_iommu_fault(iommu->domain, iommu->dev, iova,
						   flags);
			else
				dev_err(iommu->dev, "Page fault while iommu not attached to domain?\n");

			rk_iommu_base_command(iommu->bases[i], RK_MMU_CMD_ZAP_CACHE);
			rk_iommu_base_command(iommu->bases[i], RK_MMU_CMD_PAGE_FAULT_DONE);
		}

		if (int_status & RK_MMU_IRQ_BUS_ERROR)
			dev_err(iommu->dev, "BUS_ERROR occurred at %pad\n", &iova);

		if (int_status & ~RK_MMU_IRQ_MASK)
			dev_err(iommu->dev, "unexpected int_status: %#08x\n",
				int_status);

		rk_iommu_write(iommu->bases[i], RK_MMU_INT_CLEAR, int_status);
	}

	clk_bulk_disable(iommu->num_clocks, iommu->clocks);

out:
	pm_runtime_put(iommu->dev);
	return ret;
}