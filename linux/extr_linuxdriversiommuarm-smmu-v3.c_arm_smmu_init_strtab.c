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
typedef  int u64 ;
struct TYPE_2__ {int strtab_dma; int strtab_base; } ;
struct arm_smmu_device {int features; int /*<<< orphan*/  vmid_map; TYPE_1__ strtab_cfg; } ;

/* Variables and functions */
 int ARM_SMMU_FEAT_2_LVL_STRTAB ; 
 int STRTAB_BASE_ADDR_MASK ; 
 int STRTAB_BASE_RA ; 
 int arm_smmu_init_strtab_2lvl (struct arm_smmu_device*) ; 
 int arm_smmu_init_strtab_linear (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arm_smmu_init_strtab(struct arm_smmu_device *smmu)
{
	u64 reg;
	int ret;

	if (smmu->features & ARM_SMMU_FEAT_2_LVL_STRTAB)
		ret = arm_smmu_init_strtab_2lvl(smmu);
	else
		ret = arm_smmu_init_strtab_linear(smmu);

	if (ret)
		return ret;

	/* Set the strtab base address */
	reg  = smmu->strtab_cfg.strtab_dma & STRTAB_BASE_ADDR_MASK;
	reg |= STRTAB_BASE_RA;
	smmu->strtab_cfg.strtab_base = reg;

	/* Allocate the first VMID for stage-2 bypass STEs */
	set_bit(0, smmu->vmid_map);
	return 0;
}