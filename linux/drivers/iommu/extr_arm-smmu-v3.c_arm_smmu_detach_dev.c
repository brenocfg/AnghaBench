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
struct arm_smmu_master {int ats_enabled; struct arm_smmu_domain* domain; int /*<<< orphan*/  domain_head; } ;
struct arm_smmu_domain {int /*<<< orphan*/  devices_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smmu_disable_ats (struct arm_smmu_master*) ; 
 int /*<<< orphan*/  arm_smmu_install_ste_for_dev (struct arm_smmu_master*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void arm_smmu_detach_dev(struct arm_smmu_master *master)
{
	unsigned long flags;
	struct arm_smmu_domain *smmu_domain = master->domain;

	if (!smmu_domain)
		return;

	arm_smmu_disable_ats(master);

	spin_lock_irqsave(&smmu_domain->devices_lock, flags);
	list_del(&master->domain_head);
	spin_unlock_irqrestore(&smmu_domain->devices_lock, flags);

	master->domain = NULL;
	master->ats_enabled = false;
	arm_smmu_install_ste_for_dev(master);
}