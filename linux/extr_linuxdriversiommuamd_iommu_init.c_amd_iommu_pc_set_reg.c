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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int iommu_pc_get_set_reg (struct amd_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int amd_iommu_pc_set_reg(struct amd_iommu *iommu, u8 bank, u8 cntr, u8 fxn, u64 *value)
{
	if (!iommu)
		return -EINVAL;

	return iommu_pc_get_set_reg(iommu, bank, cntr, fxn, value, true);
}