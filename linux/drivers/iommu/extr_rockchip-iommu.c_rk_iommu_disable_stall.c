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
struct rk_iommu {int num_mmu; int /*<<< orphan*/ * bases; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK_MMU_CMD_DISABLE_STALL ; 
 int /*<<< orphan*/  RK_MMU_POLL_PERIOD_US ; 
 int /*<<< orphan*/  RK_MMU_POLL_TIMEOUT_US ; 
 int /*<<< orphan*/  RK_MMU_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int readx_poll_timeout (int /*<<< orphan*/  (*) (struct rk_iommu*),struct rk_iommu*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_command (struct rk_iommu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_iommu_is_stall_active (struct rk_iommu*) ; 
 int /*<<< orphan*/  rk_iommu_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk_iommu_disable_stall(struct rk_iommu *iommu)
{
	int ret, i;
	bool val;

	if (!rk_iommu_is_stall_active(iommu))
		return 0;

	rk_iommu_command(iommu, RK_MMU_CMD_DISABLE_STALL);

	ret = readx_poll_timeout(rk_iommu_is_stall_active, iommu, val,
				 !val, RK_MMU_POLL_PERIOD_US,
				 RK_MMU_POLL_TIMEOUT_US);
	if (ret)
		for (i = 0; i < iommu->num_mmu; i++)
			dev_err(iommu->dev, "Disable stall request timed out, status: %#08x\n",
				rk_iommu_read(iommu->bases[i], RK_MMU_STATUS));

	return ret;
}