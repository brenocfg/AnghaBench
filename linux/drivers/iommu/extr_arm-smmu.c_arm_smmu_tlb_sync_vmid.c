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
struct arm_smmu_domain {int /*<<< orphan*/  smmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_smmu_tlb_sync_global (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_smmu_tlb_sync_vmid(void *cookie)
{
	struct arm_smmu_domain *smmu_domain = cookie;

	arm_smmu_tlb_sync_global(smmu_domain->smmu);
}