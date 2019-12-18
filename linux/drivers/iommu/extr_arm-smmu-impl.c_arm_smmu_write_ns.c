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
struct arm_smmu_device {int dummy; } ;

/* Variables and functions */
 int ARM_SMMU_GR0 ; 
 int arm_smmu_gr0_ns (int) ; 
 scalar_t__ arm_smmu_page (struct arm_smmu_device*,int) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void arm_smmu_write_ns(struct arm_smmu_device *smmu, int page,
			      int offset, u32 val)
{
	if (page == ARM_SMMU_GR0)
		offset = arm_smmu_gr0_ns(offset);
	writel_relaxed(val, arm_smmu_page(smmu, page) + offset);
}