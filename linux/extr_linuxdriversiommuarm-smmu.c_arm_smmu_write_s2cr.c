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
typedef  int u32 ;
struct arm_smmu_s2cr {int type; int cbndx; int privcfg; } ;
struct arm_smmu_device {int features; TYPE_1__* smrs; struct arm_smmu_s2cr* s2crs; } ;
struct TYPE_2__ {scalar_t__ valid; } ;

/* Variables and functions */
 int ARM_SMMU_FEAT_EXIDS ; 
 scalar_t__ ARM_SMMU_GR0 (struct arm_smmu_device*) ; 
 scalar_t__ ARM_SMMU_GR0_S2CR (int) ; 
 int S2CR_CBNDX_MASK ; 
 int S2CR_CBNDX_SHIFT ; 
 int S2CR_EXIDVALID ; 
 int S2CR_PRIVCFG_MASK ; 
 int S2CR_PRIVCFG_SHIFT ; 
 int S2CR_TYPE_MASK ; 
 int S2CR_TYPE_SHIFT ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void arm_smmu_write_s2cr(struct arm_smmu_device *smmu, int idx)
{
	struct arm_smmu_s2cr *s2cr = smmu->s2crs + idx;
	u32 reg = (s2cr->type & S2CR_TYPE_MASK) << S2CR_TYPE_SHIFT |
		  (s2cr->cbndx & S2CR_CBNDX_MASK) << S2CR_CBNDX_SHIFT |
		  (s2cr->privcfg & S2CR_PRIVCFG_MASK) << S2CR_PRIVCFG_SHIFT;

	if (smmu->features & ARM_SMMU_FEAT_EXIDS && smmu->smrs &&
	    smmu->smrs[idx].valid)
		reg |= S2CR_EXIDVALID;
	writel_relaxed(reg, ARM_SMMU_GR0(smmu) + ARM_SMMU_GR0_S2CR(idx));
}