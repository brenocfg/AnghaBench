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
struct arm_smmu_master {int /*<<< orphan*/  dev; int /*<<< orphan*/  ats_enabled; struct arm_smmu_domain* domain; } ;
struct arm_smmu_domain {int /*<<< orphan*/  nr_ats_masters; } ;
struct arm_smmu_cmdq_ent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smmu_atc_inv_master (struct arm_smmu_master*,struct arm_smmu_cmdq_ent*) ; 
 int /*<<< orphan*/  arm_smmu_atc_inv_to_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smmu_cmdq_ent*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_ats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void arm_smmu_disable_ats(struct arm_smmu_master *master)
{
	struct arm_smmu_cmdq_ent cmd;
	struct arm_smmu_domain *smmu_domain = master->domain;

	if (!master->ats_enabled)
		return;

	pci_disable_ats(to_pci_dev(master->dev));
	/*
	 * Ensure ATS is disabled at the endpoint before we issue the
	 * ATC invalidation via the SMMU.
	 */
	wmb();
	arm_smmu_atc_inv_to_cmd(0, 0, 0, &cmd);
	arm_smmu_atc_inv_master(master, &cmd);
	atomic_dec(&smmu_domain->nr_ats_masters);
}