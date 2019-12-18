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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct smmu_pmu {int counter_mask; scalar_t__ reloc_base; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ SMMU_PMCG_EVCNTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 

__attribute__((used)) static inline u64 smmu_pmu_counter_get_value(struct smmu_pmu *smmu_pmu, u32 idx)
{
	u64 value;

	if (smmu_pmu->counter_mask & BIT(32))
		value = readq(smmu_pmu->reloc_base + SMMU_PMCG_EVCNTR(idx, 8));
	else
		value = readl(smmu_pmu->reloc_base + SMMU_PMCG_EVCNTR(idx, 4));

	return value;
}