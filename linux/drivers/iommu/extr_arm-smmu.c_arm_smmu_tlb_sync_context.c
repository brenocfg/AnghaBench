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
struct TYPE_2__ {int /*<<< orphan*/  cbndx; } ;
struct arm_smmu_domain {int /*<<< orphan*/  cb_lock; TYPE_1__ cfg; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_CB (struct arm_smmu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_SMMU_CB_TLBSTATUS ; 
 int /*<<< orphan*/  ARM_SMMU_CB_TLBSYNC ; 
 int /*<<< orphan*/  __arm_smmu_tlb_sync (struct arm_smmu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void arm_smmu_tlb_sync_context(void *cookie)
{
	struct arm_smmu_domain *smmu_domain = cookie;
	struct arm_smmu_device *smmu = smmu_domain->smmu;
	unsigned long flags;

	spin_lock_irqsave(&smmu_domain->cb_lock, flags);
	__arm_smmu_tlb_sync(smmu, ARM_SMMU_CB(smmu, smmu_domain->cfg.cbndx),
			    ARM_SMMU_CB_TLBSYNC, ARM_SMMU_CB_TLBSTATUS);
	spin_unlock_irqrestore(&smmu_domain->cb_lock, flags);
}