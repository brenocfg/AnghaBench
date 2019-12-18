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
struct rk_iommu {int num_mmu; int /*<<< orphan*/  dev; int /*<<< orphan*/ * bases; scalar_t__ reset_disabled; } ;

/* Variables and functions */
 int DTE_ADDR_DUMMY ; 
 int EFAULT ; 
 int RK_DTE_PT_ADDRESS_MASK ; 
 int /*<<< orphan*/  RK_MMU_CMD_FORCE_RESET ; 
 int /*<<< orphan*/  RK_MMU_DTE_ADDR ; 
 int /*<<< orphan*/  RK_MMU_FORCE_RESET_TIMEOUT_US ; 
 int /*<<< orphan*/  RK_MMU_POLL_TIMEOUT_US ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct rk_iommu*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_command (struct rk_iommu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_is_reset_done ; 
 int rk_iommu_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rk_iommu_force_reset(struct rk_iommu *iommu)
{
	int ret, i;
	u32 dte_addr;
	bool val;

	if (iommu->reset_disabled)
		return 0;

	/*
	 * Check if register DTE_ADDR is working by writing DTE_ADDR_DUMMY
	 * and verifying that upper 5 nybbles are read back.
	 */
	for (i = 0; i < iommu->num_mmu; i++) {
		rk_iommu_write(iommu->bases[i], RK_MMU_DTE_ADDR, DTE_ADDR_DUMMY);

		dte_addr = rk_iommu_read(iommu->bases[i], RK_MMU_DTE_ADDR);
		if (dte_addr != (DTE_ADDR_DUMMY & RK_DTE_PT_ADDRESS_MASK)) {
			dev_err(iommu->dev, "Error during raw reset. MMU_DTE_ADDR is not functioning\n");
			return -EFAULT;
		}
	}

	rk_iommu_command(iommu, RK_MMU_CMD_FORCE_RESET);

	ret = readx_poll_timeout(rk_iommu_is_reset_done, iommu, val,
				 val, RK_MMU_FORCE_RESET_TIMEOUT_US,
				 RK_MMU_POLL_TIMEOUT_US);
	if (ret) {
		dev_err(iommu->dev, "FORCE_RESET command timed out\n");
		return ret;
	}

	return 0;
}