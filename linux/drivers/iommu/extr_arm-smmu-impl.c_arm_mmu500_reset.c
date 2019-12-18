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
struct arm_smmu_device {int num_context_banks; } ;

/* Variables and functions */
 int ARM_MMU500_ACR_CACHE_LOCK ; 
 int ARM_MMU500_ACR_S2CRB_TLBEN ; 
 int ARM_MMU500_ACR_SMTNMB_TLBEN ; 
 int ARM_MMU500_ACTLR_CPRE ; 
 int /*<<< orphan*/  ARM_SMMU_CB_ACTLR ; 
 int /*<<< orphan*/  ARM_SMMU_GR0_ID7 ; 
 int /*<<< orphan*/  ARM_SMMU_GR0_sACR ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ID7_MAJOR ; 
 int arm_smmu_cb_read (struct arm_smmu_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_cb_write (struct arm_smmu_device*,int,int /*<<< orphan*/ ,int) ; 
 int arm_smmu_gr0_read (struct arm_smmu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_gr0_write (struct arm_smmu_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int arm_mmu500_reset(struct arm_smmu_device *smmu)
{
	u32 reg, major;
	int i;
	/*
	 * On MMU-500 r2p0 onwards we need to clear ACR.CACHE_LOCK before
	 * writes to the context bank ACTLRs will stick. And we just hope that
	 * Secure has also cleared SACR.CACHE_LOCK for this to take effect...
	 */
	reg = arm_smmu_gr0_read(smmu, ARM_SMMU_GR0_ID7);
	major = FIELD_GET(ID7_MAJOR, reg);
	reg = arm_smmu_gr0_read(smmu, ARM_SMMU_GR0_sACR);
	if (major >= 2)
		reg &= ~ARM_MMU500_ACR_CACHE_LOCK;
	/*
	 * Allow unmatched Stream IDs to allocate bypass
	 * TLB entries for reduced latency.
	 */
	reg |= ARM_MMU500_ACR_SMTNMB_TLBEN | ARM_MMU500_ACR_S2CRB_TLBEN;
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_sACR, reg);

	/*
	 * Disable MMU-500's not-particularly-beneficial next-page
	 * prefetcher for the sake of errata #841119 and #826419.
	 */
	for (i = 0; i < smmu->num_context_banks; ++i) {
		reg = arm_smmu_cb_read(smmu, i, ARM_SMMU_CB_ACTLR);
		reg &= ~ARM_MMU500_ACTLR_CPRE;
		arm_smmu_cb_write(smmu, i, ARM_SMMU_CB_ACTLR, reg);
	}

	return 0;
}