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
typedef  int /*<<< orphan*/  u32 ;
struct smmu_pmu {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ SMMU_PMCG_SMR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void smmu_pmu_set_smr(struct smmu_pmu *smmu_pmu, u32 idx, u32 val)
{
	writel(val, smmu_pmu->reg_base + SMMU_PMCG_SMR(idx));
}