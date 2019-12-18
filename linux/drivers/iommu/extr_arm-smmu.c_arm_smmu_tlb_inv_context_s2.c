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
struct TYPE_2__ {int /*<<< orphan*/  vmid; } ;
struct arm_smmu_domain {TYPE_1__ cfg; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_GR0_TLBIVMID ; 
 int /*<<< orphan*/  arm_smmu_gr0_write (struct arm_smmu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_tlb_sync_global (struct arm_smmu_device*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void arm_smmu_tlb_inv_context_s2(void *cookie)
{
	struct arm_smmu_domain *smmu_domain = cookie;
	struct arm_smmu_device *smmu = smmu_domain->smmu;

	/* See above */
	wmb();
	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_TLBIVMID, smmu_domain->cfg.vmid);
	arm_smmu_tlb_sync_global(smmu);
}