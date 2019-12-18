#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct arm_smmu_s2cr {int /*<<< orphan*/  privcfg; int /*<<< orphan*/  cbndx; int /*<<< orphan*/  type; } ;
struct arm_smmu_device {int features; TYPE_1__* smrs; struct arm_smmu_s2cr* s2crs; } ;
struct TYPE_2__ {scalar_t__ valid; } ;

/* Variables and functions */
 int ARM_SMMU_FEAT_EXIDS ; 
 int /*<<< orphan*/  ARM_SMMU_GR0_S2CR (int) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S2CR_CBNDX ; 
 int S2CR_EXIDVALID ; 
 int /*<<< orphan*/  S2CR_PRIVCFG ; 
 int /*<<< orphan*/  S2CR_TYPE ; 
 int /*<<< orphan*/  arm_smmu_gr0_write (struct arm_smmu_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arm_smmu_write_s2cr(struct arm_smmu_device *smmu, int idx)
{
	struct arm_smmu_s2cr *s2cr = smmu->s2crs + idx;
	u32 reg = FIELD_PREP(S2CR_TYPE, s2cr->type) |
		  FIELD_PREP(S2CR_CBNDX, s2cr->cbndx) |
		  FIELD_PREP(S2CR_PRIVCFG, s2cr->privcfg);

	if (smmu->features & ARM_SMMU_FEAT_EXIDS && smmu->smrs &&
	    smmu->smrs[idx].valid)
		reg |= S2CR_EXIDVALID;
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_S2CR(idx), reg);
}