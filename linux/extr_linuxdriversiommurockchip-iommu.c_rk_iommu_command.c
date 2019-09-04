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
typedef  int /*<<< orphan*/  u32 ;
struct rk_iommu {int num_mmu; scalar_t__* bases; } ;

/* Variables and functions */
 scalar_t__ RK_MMU_COMMAND ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rk_iommu_command(struct rk_iommu *iommu, u32 command)
{
	int i;

	for (i = 0; i < iommu->num_mmu; i++)
		writel(command, iommu->bases[i] + RK_MMU_COMMAND);
}