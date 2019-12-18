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
typedef  int u32 ;
struct arm_spe_pmu {int features; int counter_sz; int min_period; } ;

/* Variables and functions */
#define  SPE_PMU_CAP_CNT_SZ 129 
 int SPE_PMU_CAP_FEAT_MAX ; 
#define  SPE_PMU_CAP_MIN_IVAL 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int* arm_spe_pmu_feat_caps ; 

__attribute__((used)) static u32 arm_spe_pmu_cap_get(struct arm_spe_pmu *spe_pmu, int cap)
{
	if (cap < SPE_PMU_CAP_FEAT_MAX)
		return !!(spe_pmu->features & arm_spe_pmu_feat_caps[cap]);

	switch (cap) {
	case SPE_PMU_CAP_CNT_SZ:
		return spe_pmu->counter_sz;
	case SPE_PMU_CAP_MIN_IVAL:
		return spe_pmu->min_period;
	default:
		WARN(1, "unknown cap %d\n", cap);
	}

	return 0;
}