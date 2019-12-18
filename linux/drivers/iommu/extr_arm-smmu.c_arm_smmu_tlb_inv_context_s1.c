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
struct TYPE_2__ {int /*<<< orphan*/  asid; int /*<<< orphan*/  cbndx; } ;
struct arm_smmu_domain {TYPE_1__ cfg; int /*<<< orphan*/  smmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_CB_S1_TLBIASID ; 
 int /*<<< orphan*/  arm_smmu_cb_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_smmu_tlb_sync_context (void*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void arm_smmu_tlb_inv_context_s1(void *cookie)
{
	struct arm_smmu_domain *smmu_domain = cookie;
	/*
	 * The TLBI write may be relaxed, so ensure that PTEs cleared by the
	 * current CPU are visible beforehand.
	 */
	wmb();
	arm_smmu_cb_write(smmu_domain->smmu, smmu_domain->cfg.cbndx,
			  ARM_SMMU_CB_S1_TLBIASID, smmu_domain->cfg.asid);
	arm_smmu_tlb_sync_context(cookie);
}