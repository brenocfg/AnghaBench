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
struct rk_iommu {int num_mmu; int /*<<< orphan*/ * bases; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK_MMU_DTE_ADDR ; 
 scalar_t__ rk_iommu_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rk_iommu_is_reset_done(struct rk_iommu *iommu)
{
	bool done = true;
	int i;

	for (i = 0; i < iommu->num_mmu; i++)
		done &= rk_iommu_read(iommu->bases[i], RK_MMU_DTE_ADDR) == 0;

	return done;
}