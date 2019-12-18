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
struct arm_smmu_device {void* smr_mask_mask; void* streamid_mask; int /*<<< orphan*/  smrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_GR0_SMR (int /*<<< orphan*/ ) ; 
 void* FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  SMR_ID ; 
 int /*<<< orphan*/  SMR_MASK ; 
 int /*<<< orphan*/  arm_smmu_gr0_read (struct arm_smmu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_gr0_write (struct arm_smmu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_smmu_test_smr_masks(struct arm_smmu_device *smmu)
{
	u32 smr;

	if (!smmu->smrs)
		return;

	/*
	 * SMR.ID bits may not be preserved if the corresponding MASK
	 * bits are set, so check each one separately. We can reject
	 * masters later if they try to claim IDs outside these masks.
	 */
	smr = FIELD_PREP(SMR_ID, smmu->streamid_mask);
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_SMR(0), smr);
	smr = arm_smmu_gr0_read(smmu, ARM_SMMU_GR0_SMR(0));
	smmu->streamid_mask = FIELD_GET(SMR_ID, smr);

	smr = FIELD_PREP(SMR_MASK, smmu->streamid_mask);
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_SMR(0), smr);
	smr = arm_smmu_gr0_read(smmu, ARM_SMMU_GR0_SMR(0));
	smmu->smr_mask_mask = FIELD_GET(SMR_MASK, smr);
}