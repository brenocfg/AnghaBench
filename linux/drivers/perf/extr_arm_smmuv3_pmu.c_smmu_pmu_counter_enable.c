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
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ SMMU_PMCG_CNTENSET0 ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void smmu_pmu_counter_enable(struct smmu_pmu *smmu_pmu, u32 idx)
{
	writeq(BIT(idx), smmu_pmu->reg_base + SMMU_PMCG_CNTENSET0);
}