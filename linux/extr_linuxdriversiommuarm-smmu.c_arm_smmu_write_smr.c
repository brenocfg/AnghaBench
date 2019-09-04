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
struct arm_smmu_smr {int id; int mask; scalar_t__ valid; } ;
struct arm_smmu_device {int features; struct arm_smmu_smr* smrs; } ;

/* Variables and functions */
 int ARM_SMMU_FEAT_EXIDS ; 
 scalar_t__ ARM_SMMU_GR0 (struct arm_smmu_device*) ; 
 scalar_t__ ARM_SMMU_GR0_SMR (int) ; 
 int SMR_ID_SHIFT ; 
 int SMR_MASK_SHIFT ; 
 int SMR_VALID ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void arm_smmu_write_smr(struct arm_smmu_device *smmu, int idx)
{
	struct arm_smmu_smr *smr = smmu->smrs + idx;
	u32 reg = smr->id << SMR_ID_SHIFT | smr->mask << SMR_MASK_SHIFT;

	if (!(smmu->features & ARM_SMMU_FEAT_EXIDS) && smr->valid)
		reg |= SMR_VALID;
	writel_relaxed(reg, ARM_SMMU_GR0(smmu) + ARM_SMMU_GR0_SMR(idx));
}