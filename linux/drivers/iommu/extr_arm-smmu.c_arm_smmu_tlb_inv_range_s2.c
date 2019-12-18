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
struct TYPE_2__ {int cbndx; scalar_t__ fmt; } ;
struct arm_smmu_domain {TYPE_1__ cfg; struct arm_smmu_device* smmu; } ;
struct arm_smmu_device {int features; } ;

/* Variables and functions */
 int ARM_SMMU_CB_S2_TLBIIPAS2 ; 
 int ARM_SMMU_CB_S2_TLBIIPAS2L ; 
 scalar_t__ ARM_SMMU_CTX_FMT_AARCH64 ; 
 int ARM_SMMU_FEAT_COHERENT_WALK ; 
 int /*<<< orphan*/  arm_smmu_cb_write (struct arm_smmu_device*,int,int,unsigned long) ; 
 int /*<<< orphan*/  arm_smmu_cb_writeq (struct arm_smmu_device*,int,int,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void arm_smmu_tlb_inv_range_s2(unsigned long iova, size_t size,
				      size_t granule, bool leaf, void *cookie)
{
	struct arm_smmu_domain *smmu_domain = cookie;
	struct arm_smmu_device *smmu = smmu_domain->smmu;
	int reg, idx = smmu_domain->cfg.cbndx;

	if (smmu->features & ARM_SMMU_FEAT_COHERENT_WALK)
		wmb();

	reg = leaf ? ARM_SMMU_CB_S2_TLBIIPAS2L : ARM_SMMU_CB_S2_TLBIIPAS2;
	iova >>= 12;
	do {
		if (smmu_domain->cfg.fmt == ARM_SMMU_CTX_FMT_AARCH64)
			arm_smmu_cb_writeq(smmu, idx, reg, iova);
		else
			arm_smmu_cb_write(smmu, idx, reg, iova);
		iova += granule >> 12;
	} while (size -= granule);
}