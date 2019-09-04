#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_13__ {int prod; int cons; int /*<<< orphan*/  q_base; } ;
struct TYPE_14__ {TYPE_6__ q; } ;
struct TYPE_11__ {int prod; int cons; int /*<<< orphan*/  q_base; } ;
struct TYPE_12__ {TYPE_4__ q; } ;
struct TYPE_9__ {int prod; int cons; int /*<<< orphan*/  q_base; } ;
struct TYPE_10__ {TYPE_2__ q; } ;
struct TYPE_8__ {int strtab_base_cfg; int /*<<< orphan*/  strtab_base; } ;
struct arm_smmu_device {int features; int /*<<< orphan*/  dev; TYPE_7__ priq; scalar_t__ base; TYPE_5__ evtq; TYPE_3__ cmdq; TYPE_1__ strtab_cfg; } ;
struct arm_smmu_cmdq_ent {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 scalar_t__ ARM_SMMU_CMDQ_BASE ; 
 scalar_t__ ARM_SMMU_CMDQ_CONS ; 
 scalar_t__ ARM_SMMU_CMDQ_PROD ; 
 scalar_t__ ARM_SMMU_CR0 ; 
 int /*<<< orphan*/  ARM_SMMU_CR0ACK ; 
 scalar_t__ ARM_SMMU_CR1 ; 
 scalar_t__ ARM_SMMU_CR2 ; 
 scalar_t__ ARM_SMMU_EVTQ_BASE ; 
 int /*<<< orphan*/  ARM_SMMU_EVTQ_CONS ; 
 int /*<<< orphan*/  ARM_SMMU_EVTQ_PROD ; 
 int ARM_SMMU_FEAT_HYP ; 
 int ARM_SMMU_FEAT_PRI ; 
 scalar_t__ ARM_SMMU_PRIQ_BASE ; 
 int /*<<< orphan*/  ARM_SMMU_PRIQ_CONS ; 
 int /*<<< orphan*/  ARM_SMMU_PRIQ_PROD ; 
 int /*<<< orphan*/  ARM_SMMU_SH_ISH ; 
 scalar_t__ ARM_SMMU_STRTAB_BASE ; 
 scalar_t__ ARM_SMMU_STRTAB_BASE_CFG ; 
 int /*<<< orphan*/  CMDQ_OP_CFGI_ALL ; 
 int /*<<< orphan*/  CMDQ_OP_TLBI_EL2_ALL ; 
 int /*<<< orphan*/  CMDQ_OP_TLBI_NSNH_ALL ; 
 int CR0_CMDQEN ; 
 int CR0_EVTQEN ; 
 int CR0_PRIQEN ; 
 int CR0_SMMUEN ; 
 int /*<<< orphan*/  CR1_CACHE_WB ; 
 int /*<<< orphan*/  CR1_QUEUE_IC ; 
 int /*<<< orphan*/  CR1_QUEUE_OC ; 
 int /*<<< orphan*/  CR1_QUEUE_SH ; 
 int /*<<< orphan*/  CR1_TABLE_IC ; 
 int /*<<< orphan*/  CR1_TABLE_OC ; 
 int /*<<< orphan*/  CR1_TABLE_SH ; 
 int CR2_E2H ; 
 int CR2_PTM ; 
 int CR2_RECINVSID ; 
 int EBUSY ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GBPA_ABORT ; 
 int /*<<< orphan*/  arm_smmu_cmdq_issue_cmd (struct arm_smmu_device*,struct arm_smmu_cmdq_ent*) ; 
 int /*<<< orphan*/  arm_smmu_cmdq_issue_sync (struct arm_smmu_device*) ; 
 int arm_smmu_device_disable (struct arm_smmu_device*) ; 
 scalar_t__ arm_smmu_page1_fixup (int /*<<< orphan*/ ,struct arm_smmu_device*) ; 
 int arm_smmu_setup_irqs (struct arm_smmu_device*) ; 
 int arm_smmu_update_gbpa (struct arm_smmu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int arm_smmu_write_reg_sync (struct arm_smmu_device*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ disable_bypass ; 
 scalar_t__ is_kdump_kernel () ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 
 int /*<<< orphan*/  writeq_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int arm_smmu_device_reset(struct arm_smmu_device *smmu, bool bypass)
{
	int ret;
	u32 reg, enables;
	struct arm_smmu_cmdq_ent cmd;

	/* Clear CR0 and sync (disables SMMU and queue processing) */
	reg = readl_relaxed(smmu->base + ARM_SMMU_CR0);
	if (reg & CR0_SMMUEN) {
		if (is_kdump_kernel()) {
			arm_smmu_update_gbpa(smmu, GBPA_ABORT, 0);
			arm_smmu_device_disable(smmu);
			return -EBUSY;
		}

		dev_warn(smmu->dev, "SMMU currently enabled! Resetting...\n");
	}

	ret = arm_smmu_device_disable(smmu);
	if (ret)
		return ret;

	/* CR1 (table and queue memory attributes) */
	reg = FIELD_PREP(CR1_TABLE_SH, ARM_SMMU_SH_ISH) |
	      FIELD_PREP(CR1_TABLE_OC, CR1_CACHE_WB) |
	      FIELD_PREP(CR1_TABLE_IC, CR1_CACHE_WB) |
	      FIELD_PREP(CR1_QUEUE_SH, ARM_SMMU_SH_ISH) |
	      FIELD_PREP(CR1_QUEUE_OC, CR1_CACHE_WB) |
	      FIELD_PREP(CR1_QUEUE_IC, CR1_CACHE_WB);
	writel_relaxed(reg, smmu->base + ARM_SMMU_CR1);

	/* CR2 (random crap) */
	reg = CR2_PTM | CR2_RECINVSID | CR2_E2H;
	writel_relaxed(reg, smmu->base + ARM_SMMU_CR2);

	/* Stream table */
	writeq_relaxed(smmu->strtab_cfg.strtab_base,
		       smmu->base + ARM_SMMU_STRTAB_BASE);
	writel_relaxed(smmu->strtab_cfg.strtab_base_cfg,
		       smmu->base + ARM_SMMU_STRTAB_BASE_CFG);

	/* Command queue */
	writeq_relaxed(smmu->cmdq.q.q_base, smmu->base + ARM_SMMU_CMDQ_BASE);
	writel_relaxed(smmu->cmdq.q.prod, smmu->base + ARM_SMMU_CMDQ_PROD);
	writel_relaxed(smmu->cmdq.q.cons, smmu->base + ARM_SMMU_CMDQ_CONS);

	enables = CR0_CMDQEN;
	ret = arm_smmu_write_reg_sync(smmu, enables, ARM_SMMU_CR0,
				      ARM_SMMU_CR0ACK);
	if (ret) {
		dev_err(smmu->dev, "failed to enable command queue\n");
		return ret;
	}

	/* Invalidate any cached configuration */
	cmd.opcode = CMDQ_OP_CFGI_ALL;
	arm_smmu_cmdq_issue_cmd(smmu, &cmd);
	arm_smmu_cmdq_issue_sync(smmu);

	/* Invalidate any stale TLB entries */
	if (smmu->features & ARM_SMMU_FEAT_HYP) {
		cmd.opcode = CMDQ_OP_TLBI_EL2_ALL;
		arm_smmu_cmdq_issue_cmd(smmu, &cmd);
	}

	cmd.opcode = CMDQ_OP_TLBI_NSNH_ALL;
	arm_smmu_cmdq_issue_cmd(smmu, &cmd);
	arm_smmu_cmdq_issue_sync(smmu);

	/* Event queue */
	writeq_relaxed(smmu->evtq.q.q_base, smmu->base + ARM_SMMU_EVTQ_BASE);
	writel_relaxed(smmu->evtq.q.prod,
		       arm_smmu_page1_fixup(ARM_SMMU_EVTQ_PROD, smmu));
	writel_relaxed(smmu->evtq.q.cons,
		       arm_smmu_page1_fixup(ARM_SMMU_EVTQ_CONS, smmu));

	enables |= CR0_EVTQEN;
	ret = arm_smmu_write_reg_sync(smmu, enables, ARM_SMMU_CR0,
				      ARM_SMMU_CR0ACK);
	if (ret) {
		dev_err(smmu->dev, "failed to enable event queue\n");
		return ret;
	}

	/* PRI queue */
	if (smmu->features & ARM_SMMU_FEAT_PRI) {
		writeq_relaxed(smmu->priq.q.q_base,
			       smmu->base + ARM_SMMU_PRIQ_BASE);
		writel_relaxed(smmu->priq.q.prod,
			       arm_smmu_page1_fixup(ARM_SMMU_PRIQ_PROD, smmu));
		writel_relaxed(smmu->priq.q.cons,
			       arm_smmu_page1_fixup(ARM_SMMU_PRIQ_CONS, smmu));

		enables |= CR0_PRIQEN;
		ret = arm_smmu_write_reg_sync(smmu, enables, ARM_SMMU_CR0,
					      ARM_SMMU_CR0ACK);
		if (ret) {
			dev_err(smmu->dev, "failed to enable PRI queue\n");
			return ret;
		}
	}

	ret = arm_smmu_setup_irqs(smmu);
	if (ret) {
		dev_err(smmu->dev, "failed to setup irqs\n");
		return ret;
	}


	/* Enable the SMMU interface, or ensure bypass */
	if (!bypass || disable_bypass) {
		enables |= CR0_SMMUEN;
	} else {
		ret = arm_smmu_update_gbpa(smmu, 0, GBPA_ABORT);
		if (ret)
			return ret;
	}
	ret = arm_smmu_write_reg_sync(smmu, enables, ARM_SMMU_CR0,
				      ARM_SMMU_CR0ACK);
	if (ret) {
		dev_err(smmu->dev, "failed to enable SMMU interface\n");
		return ret;
	}

	return 0;
}