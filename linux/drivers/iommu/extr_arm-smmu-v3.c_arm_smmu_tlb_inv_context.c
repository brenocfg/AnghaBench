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
struct TYPE_8__ {scalar_t__ vmid; } ;
struct TYPE_5__ {int /*<<< orphan*/  asid; } ;
struct TYPE_6__ {TYPE_1__ cd; } ;
struct arm_smmu_domain {scalar_t__ stage; TYPE_4__ s2_cfg; TYPE_2__ s1_cfg; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int dummy; } ;
struct TYPE_7__ {scalar_t__ vmid; int /*<<< orphan*/  asid; } ;
struct arm_smmu_cmdq_ent {TYPE_3__ tlbi; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 scalar_t__ ARM_SMMU_DOMAIN_S1 ; 
 int /*<<< orphan*/  CMDQ_OP_TLBI_NH_ASID ; 
 int /*<<< orphan*/  CMDQ_OP_TLBI_S12_VMALL ; 
 int /*<<< orphan*/  arm_smmu_atc_inv_domain (struct arm_smmu_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_cmdq_issue_cmd (struct arm_smmu_device*,struct arm_smmu_cmdq_ent*) ; 
 int /*<<< orphan*/  arm_smmu_cmdq_issue_sync (struct arm_smmu_device*) ; 

__attribute__((used)) static void arm_smmu_tlb_inv_context(void *cookie)
{
	struct arm_smmu_domain *smmu_domain = cookie;
	struct arm_smmu_device *smmu = smmu_domain->smmu;
	struct arm_smmu_cmdq_ent cmd;

	if (smmu_domain->stage == ARM_SMMU_DOMAIN_S1) {
		cmd.opcode	= CMDQ_OP_TLBI_NH_ASID;
		cmd.tlbi.asid	= smmu_domain->s1_cfg.cd.asid;
		cmd.tlbi.vmid	= 0;
	} else {
		cmd.opcode	= CMDQ_OP_TLBI_S12_VMALL;
		cmd.tlbi.vmid	= smmu_domain->s2_cfg.vmid;
	}

	/*
	 * NOTE: when io-pgtable is in non-strict mode, we may get here with
	 * PTEs previously cleared by unmaps on the current CPU not yet visible
	 * to the SMMU. We are relying on the dma_wmb() implicit during cmd
	 * insertion to guarantee those are observed before the TLBI. Do be
	 * careful, 007.
	 */
	arm_smmu_cmdq_issue_cmd(smmu, &cmd);
	arm_smmu_cmdq_issue_sync(smmu);
	arm_smmu_atc_inv_domain(smmu_domain, 0, 0, 0);
}