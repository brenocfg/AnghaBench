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
struct arm_smmu_device {int num_mapping_groups; int num_context_banks; int features; TYPE_1__* impl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct arm_smmu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_CB_FSR ; 
 int ARM_SMMU_FEAT_EXIDS ; 
 int ARM_SMMU_FEAT_VMID16 ; 
 int /*<<< orphan*/  ARM_SMMU_GR0_TLBIALLH ; 
 int /*<<< orphan*/  ARM_SMMU_GR0_TLBIALLNSNH ; 
 int /*<<< orphan*/  ARM_SMMU_GR0_sCR0 ; 
 int /*<<< orphan*/  ARM_SMMU_GR0_sGFSR ; 
 int /*<<< orphan*/  FSR_FAULT ; 
 int QCOM_DUMMY_VAL ; 
 int /*<<< orphan*/  arm_smmu_cb_write (struct arm_smmu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int arm_smmu_gr0_read (struct arm_smmu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_gr0_write (struct arm_smmu_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arm_smmu_tlb_sync_global (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  arm_smmu_write_context_bank (struct arm_smmu_device*,int) ; 
 int /*<<< orphan*/  arm_smmu_write_sme (struct arm_smmu_device*,int) ; 
 scalar_t__ disable_bypass ; 
 int sCR0_BSU ; 
 int sCR0_CLIENTPD ; 
 int sCR0_EXIDENABLE ; 
 int sCR0_FB ; 
 int sCR0_GCFGFIE ; 
 int sCR0_GCFGFRE ; 
 int sCR0_GFIE ; 
 int sCR0_GFRE ; 
 int sCR0_PTM ; 
 int sCR0_USFCFG ; 
 int sCR0_VMID16EN ; 
 int sCR0_VMIDPNE ; 
 int /*<<< orphan*/  stub1 (struct arm_smmu_device*) ; 

__attribute__((used)) static void arm_smmu_device_reset(struct arm_smmu_device *smmu)
{
	int i;
	u32 reg;

	/* clear global FSR */
	reg = arm_smmu_gr0_read(smmu, ARM_SMMU_GR0_sGFSR);
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_sGFSR, reg);

	/*
	 * Reset stream mapping groups: Initial values mark all SMRn as
	 * invalid and all S2CRn as bypass unless overridden.
	 */
	for (i = 0; i < smmu->num_mapping_groups; ++i)
		arm_smmu_write_sme(smmu, i);

	/* Make sure all context banks are disabled and clear CB_FSR  */
	for (i = 0; i < smmu->num_context_banks; ++i) {
		arm_smmu_write_context_bank(smmu, i);
		arm_smmu_cb_write(smmu, i, ARM_SMMU_CB_FSR, FSR_FAULT);
	}

	/* Invalidate the TLB, just in case */
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_TLBIALLH, QCOM_DUMMY_VAL);
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_TLBIALLNSNH, QCOM_DUMMY_VAL);

	reg = arm_smmu_gr0_read(smmu, ARM_SMMU_GR0_sCR0);

	/* Enable fault reporting */
	reg |= (sCR0_GFRE | sCR0_GFIE | sCR0_GCFGFRE | sCR0_GCFGFIE);

	/* Disable TLB broadcasting. */
	reg |= (sCR0_VMIDPNE | sCR0_PTM);

	/* Enable client access, handling unmatched streams as appropriate */
	reg &= ~sCR0_CLIENTPD;
	if (disable_bypass)
		reg |= sCR0_USFCFG;
	else
		reg &= ~sCR0_USFCFG;

	/* Disable forced broadcasting */
	reg &= ~sCR0_FB;

	/* Don't upgrade barriers */
	reg &= ~(sCR0_BSU);

	if (smmu->features & ARM_SMMU_FEAT_VMID16)
		reg |= sCR0_VMID16EN;

	if (smmu->features & ARM_SMMU_FEAT_EXIDS)
		reg |= sCR0_EXIDENABLE;

	if (smmu->impl && smmu->impl->reset)
		smmu->impl->reset(smmu);

	/* Push the button */
	arm_smmu_tlb_sync_global(smmu);
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_sCR0, reg);
}