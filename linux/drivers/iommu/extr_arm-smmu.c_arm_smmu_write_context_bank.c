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
struct arm_smmu_device {scalar_t__ version; int features; struct arm_smmu_cb* cbs; } ;
struct arm_smmu_cfg {scalar_t__ cbar; scalar_t__ fmt; scalar_t__ vmid; scalar_t__ irptndx; int asid; } ;
struct arm_smmu_cb {int* tcr; int* ttbr; int* mair; struct arm_smmu_cfg* cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_CB_CONTEXTIDR ; 
 int /*<<< orphan*/  ARM_SMMU_CB_S1_MAIR0 ; 
 int /*<<< orphan*/  ARM_SMMU_CB_S1_MAIR1 ; 
 int /*<<< orphan*/  ARM_SMMU_CB_SCTLR ; 
 int /*<<< orphan*/  ARM_SMMU_CB_TCR ; 
 int /*<<< orphan*/  ARM_SMMU_CB_TCR2 ; 
 int /*<<< orphan*/  ARM_SMMU_CB_TTBR0 ; 
 int /*<<< orphan*/  ARM_SMMU_CB_TTBR1 ; 
 scalar_t__ ARM_SMMU_CTX_FMT_AARCH32_S ; 
 scalar_t__ ARM_SMMU_CTX_FMT_AARCH64 ; 
 int ARM_SMMU_FEAT_VMID16 ; 
 int /*<<< orphan*/  ARM_SMMU_GR1_CBA2R (int) ; 
 int /*<<< orphan*/  ARM_SMMU_GR1_CBAR (int) ; 
 scalar_t__ ARM_SMMU_V1 ; 
 scalar_t__ ARM_SMMU_V2 ; 
 int CBA2R_VA64 ; 
 int /*<<< orphan*/  CBA2R_VMID16 ; 
 int /*<<< orphan*/  CBAR_IRPTNDX ; 
 int /*<<< orphan*/  CBAR_S1_BPSHCFG ; 
 scalar_t__ CBAR_S1_BPSHCFG_NSH ; 
 int /*<<< orphan*/  CBAR_S1_MEMATTR ; 
 scalar_t__ CBAR_S1_MEMATTR_WB ; 
 int /*<<< orphan*/  CBAR_TYPE ; 
 scalar_t__ CBAR_TYPE_S2_TRANS ; 
 int /*<<< orphan*/  CBAR_VMID ; 
 int /*<<< orphan*/  CONFIG_CPU_BIG_ENDIAN ; 
 int FIELD_PREP (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int SCTLR_AFE ; 
 int SCTLR_CFIE ; 
 int SCTLR_CFRE ; 
 int SCTLR_E ; 
 int SCTLR_M ; 
 int SCTLR_S1_ASIDPNE ; 
 int SCTLR_TRE ; 
 int /*<<< orphan*/  arm_smmu_cb_write (struct arm_smmu_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arm_smmu_cb_writeq (struct arm_smmu_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arm_smmu_gr1_write (struct arm_smmu_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void arm_smmu_write_context_bank(struct arm_smmu_device *smmu, int idx)
{
	u32 reg;
	bool stage1;
	struct arm_smmu_cb *cb = &smmu->cbs[idx];
	struct arm_smmu_cfg *cfg = cb->cfg;

	/* Unassigned context banks only need disabling */
	if (!cfg) {
		arm_smmu_cb_write(smmu, idx, ARM_SMMU_CB_SCTLR, 0);
		return;
	}

	stage1 = cfg->cbar != CBAR_TYPE_S2_TRANS;

	/* CBA2R */
	if (smmu->version > ARM_SMMU_V1) {
		if (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH64)
			reg = CBA2R_VA64;
		else
			reg = 0;
		/* 16-bit VMIDs live in CBA2R */
		if (smmu->features & ARM_SMMU_FEAT_VMID16)
			reg |= FIELD_PREP(CBA2R_VMID16, cfg->vmid);

		arm_smmu_gr1_write(smmu, ARM_SMMU_GR1_CBA2R(idx), reg);
	}

	/* CBAR */
	reg = FIELD_PREP(CBAR_TYPE, cfg->cbar);
	if (smmu->version < ARM_SMMU_V2)
		reg |= FIELD_PREP(CBAR_IRPTNDX, cfg->irptndx);

	/*
	 * Use the weakest shareability/memory types, so they are
	 * overridden by the ttbcr/pte.
	 */
	if (stage1) {
		reg |= FIELD_PREP(CBAR_S1_BPSHCFG, CBAR_S1_BPSHCFG_NSH) |
			FIELD_PREP(CBAR_S1_MEMATTR, CBAR_S1_MEMATTR_WB);
	} else if (!(smmu->features & ARM_SMMU_FEAT_VMID16)) {
		/* 8-bit VMIDs live in CBAR */
		reg |= FIELD_PREP(CBAR_VMID, cfg->vmid);
	}
	arm_smmu_gr1_write(smmu, ARM_SMMU_GR1_CBAR(idx), reg);

	/*
	 * TCR
	 * We must write this before the TTBRs, since it determines the
	 * access behaviour of some fields (in particular, ASID[15:8]).
	 */
	if (stage1 && smmu->version > ARM_SMMU_V1)
		arm_smmu_cb_write(smmu, idx, ARM_SMMU_CB_TCR2, cb->tcr[1]);
	arm_smmu_cb_write(smmu, idx, ARM_SMMU_CB_TCR, cb->tcr[0]);

	/* TTBRs */
	if (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH32_S) {
		arm_smmu_cb_write(smmu, idx, ARM_SMMU_CB_CONTEXTIDR, cfg->asid);
		arm_smmu_cb_write(smmu, idx, ARM_SMMU_CB_TTBR0, cb->ttbr[0]);
		arm_smmu_cb_write(smmu, idx, ARM_SMMU_CB_TTBR1, cb->ttbr[1]);
	} else {
		arm_smmu_cb_writeq(smmu, idx, ARM_SMMU_CB_TTBR0, cb->ttbr[0]);
		if (stage1)
			arm_smmu_cb_writeq(smmu, idx, ARM_SMMU_CB_TTBR1,
					   cb->ttbr[1]);
	}

	/* MAIRs (stage-1 only) */
	if (stage1) {
		arm_smmu_cb_write(smmu, idx, ARM_SMMU_CB_S1_MAIR0, cb->mair[0]);
		arm_smmu_cb_write(smmu, idx, ARM_SMMU_CB_S1_MAIR1, cb->mair[1]);
	}

	/* SCTLR */
	reg = SCTLR_CFIE | SCTLR_CFRE | SCTLR_AFE | SCTLR_TRE | SCTLR_M;
	if (stage1)
		reg |= SCTLR_S1_ASIDPNE;
	if (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		reg |= SCTLR_E;

	arm_smmu_cb_write(smmu, idx, ARM_SMMU_CB_SCTLR, reg);
}