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
typedef  scalar_t__ u32 ;
struct dsu_pmu {scalar_t__ num_counters; } ;

/* Variables and functions */
 scalar_t__ DSU_PMU_IDX_CYCLE_COUNTER ; 

__attribute__((used)) static inline bool dsu_pmu_counter_valid(struct dsu_pmu *dsu_pmu, u32 idx)
{
	return (idx < dsu_pmu->num_counters) ||
	       (idx == DSU_PMU_IDX_CYCLE_COUNTER);
}