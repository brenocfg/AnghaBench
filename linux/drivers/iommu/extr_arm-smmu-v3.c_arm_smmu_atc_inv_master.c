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
struct arm_smmu_master {int num_sids; int /*<<< orphan*/  smmu; int /*<<< orphan*/ * sids; int /*<<< orphan*/  ats_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  sid; } ;
struct arm_smmu_cmdq_ent {TYPE_1__ atc; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smmu_cmdq_issue_cmd (int /*<<< orphan*/ ,struct arm_smmu_cmdq_ent*) ; 
 int arm_smmu_cmdq_issue_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arm_smmu_atc_inv_master(struct arm_smmu_master *master,
				   struct arm_smmu_cmdq_ent *cmd)
{
	int i;

	if (!master->ats_enabled)
		return 0;

	for (i = 0; i < master->num_sids; i++) {
		cmd->atc.sid = master->sids[i];
		arm_smmu_cmdq_issue_cmd(master->smmu, cmd);
	}

	return arm_smmu_cmdq_issue_sync(master->smmu);
}