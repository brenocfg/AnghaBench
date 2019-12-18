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
struct arm_smmu_device {int features; } ;

/* Variables and functions */
 int ARM_SMMU_FEAT_COHERENT_WALK ; 
 int /*<<< orphan*/  ARM_SMMU_GR0_TLBIVMID ; 
 int /*<<< orphan*/  arm_smmu_gr0_write (struct arm_smmu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void arm_smmu_tlb_inv_vmid_nosync(unsigned long iova, size_t size,
					 size_t granule, bool leaf, void *cookie)
{
	struct arm_smmu_domain *smmu_domain = cookie;
	struct arm_smmu_device *smmu = smmu_domain->smmu;

	if (smmu->features & ARM_SMMU_FEAT_COHERENT_WALK)
		wmb();

	arm_smmu_gr0_write(smmu, ARM_SMMU_GR0_TLBIVMID, smmu_domain->cfg.vmid);
}