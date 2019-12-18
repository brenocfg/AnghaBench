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
struct arm_smmu_device {scalar_t__ smrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smmu_write_s2cr (struct arm_smmu_device*,int) ; 
 int /*<<< orphan*/  arm_smmu_write_smr (struct arm_smmu_device*,int) ; 

__attribute__((used)) static void arm_smmu_write_sme(struct arm_smmu_device *smmu, int idx)
{
	arm_smmu_write_s2cr(smmu, idx);
	if (smmu->smrs)
		arm_smmu_write_smr(smmu, idx);
}