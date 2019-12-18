#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tcr; int* ttbr; int /*<<< orphan*/ * mair; } ;
struct TYPE_7__ {int tcr; int* ttbr; int /*<<< orphan*/  nmrr; int /*<<< orphan*/  prrr; } ;
struct TYPE_6__ {int vtcr; int vttbr; } ;
struct io_pgtable_cfg {TYPE_4__ arm_lpae_s1_cfg; TYPE_3__ arm_v7s_cfg; TYPE_2__ arm_lpae_s2_cfg; } ;
struct arm_smmu_cfg {size_t cbndx; scalar_t__ cbar; scalar_t__ fmt; int /*<<< orphan*/  asid; } ;
struct arm_smmu_domain {TYPE_1__* smmu; struct arm_smmu_cfg cfg; } ;
struct arm_smmu_cb {int* tcr; int* ttbr; int /*<<< orphan*/ * mair; struct arm_smmu_cfg* cfg; } ;
struct TYPE_5__ {struct arm_smmu_cb* cbs; } ;

/* Variables and functions */
 scalar_t__ ARM_SMMU_CTX_FMT_AARCH32_S ; 
 scalar_t__ ARM_SMMU_CTX_FMT_AARCH64 ; 
 scalar_t__ CBAR_TYPE_S2_TRANS ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TCR2_AS ; 
 int /*<<< orphan*/  TCR2_SEP ; 
 int /*<<< orphan*/  TCR2_SEP_UPSTREAM ; 
 int /*<<< orphan*/  TTBRn_ASID ; 

__attribute__((used)) static void arm_smmu_init_context_bank(struct arm_smmu_domain *smmu_domain,
				       struct io_pgtable_cfg *pgtbl_cfg)
{
	struct arm_smmu_cfg *cfg = &smmu_domain->cfg;
	struct arm_smmu_cb *cb = &smmu_domain->smmu->cbs[cfg->cbndx];
	bool stage1 = cfg->cbar != CBAR_TYPE_S2_TRANS;

	cb->cfg = cfg;

	/* TCR */
	if (stage1) {
		if (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH32_S) {
			cb->tcr[0] = pgtbl_cfg->arm_v7s_cfg.tcr;
		} else {
			cb->tcr[0] = pgtbl_cfg->arm_lpae_s1_cfg.tcr;
			cb->tcr[1] = pgtbl_cfg->arm_lpae_s1_cfg.tcr >> 32;
			cb->tcr[1] |= FIELD_PREP(TCR2_SEP, TCR2_SEP_UPSTREAM);
			if (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH64)
				cb->tcr[1] |= TCR2_AS;
		}
	} else {
		cb->tcr[0] = pgtbl_cfg->arm_lpae_s2_cfg.vtcr;
	}

	/* TTBRs */
	if (stage1) {
		if (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH32_S) {
			cb->ttbr[0] = pgtbl_cfg->arm_v7s_cfg.ttbr[0];
			cb->ttbr[1] = pgtbl_cfg->arm_v7s_cfg.ttbr[1];
		} else {
			cb->ttbr[0] = pgtbl_cfg->arm_lpae_s1_cfg.ttbr[0];
			cb->ttbr[0] |= FIELD_PREP(TTBRn_ASID, cfg->asid);
			cb->ttbr[1] = pgtbl_cfg->arm_lpae_s1_cfg.ttbr[1];
			cb->ttbr[1] |= FIELD_PREP(TTBRn_ASID, cfg->asid);
		}
	} else {
		cb->ttbr[0] = pgtbl_cfg->arm_lpae_s2_cfg.vttbr;
	}

	/* MAIRs (stage-1 only) */
	if (stage1) {
		if (cfg->fmt == ARM_SMMU_CTX_FMT_AARCH32_S) {
			cb->mair[0] = pgtbl_cfg->arm_v7s_cfg.prrr;
			cb->mair[1] = pgtbl_cfg->arm_v7s_cfg.nmrr;
		} else {
			cb->mair[0] = pgtbl_cfg->arm_lpae_s1_cfg.mair[0];
			cb->mair[1] = pgtbl_cfg->arm_lpae_s1_cfg.mair[1];
		}
	}
}