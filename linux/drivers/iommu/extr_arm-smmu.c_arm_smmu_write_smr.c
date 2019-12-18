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
struct arm_smmu_smr {scalar_t__ valid; int /*<<< orphan*/  mask; int /*<<< orphan*/  id; } ;
struct arm_smmu_device {int features; struct arm_smmu_smr* smrs; } ;

/* Variables and functions */
 int ARM_SMMU_FEAT_EXIDS ; 
 int /*<<< orphan*/  ARM_SMMU_GR0_SMR (int) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMR_ID ; 
 int /*<<< orphan*/  SMR_MASK ; 
 int SMR_VALID ; 
 int /*<<< orphan*/  arm_smmu_gr0_write (struct arm_smmu_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arm_smmu_write_smr(struct arm_smmu_device *smmu, int idx)
{
	struct arm_smmu_smr *smr = smmu->smrs + idx;
	u32 reg = FIELD_PREP(SMR_ID, smr->id) | FIELD_PREP(SMR_MASK, smr->mask);

	if (!(smmu->features & ARM_SMMU_FEAT_EXIDS) && smr->valid)
		reg |= SMR_VALID;
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_SMR(idx), reg);
}