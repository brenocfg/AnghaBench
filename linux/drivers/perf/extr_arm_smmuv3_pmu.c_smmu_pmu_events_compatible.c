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
struct perf_event {scalar_t__ pmu; } ;
struct TYPE_2__ {scalar_t__ global_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  smmu_pmu_check_global_filter (struct perf_event*,struct perf_event*) ; 
 TYPE_1__* to_smmu_pmu (scalar_t__) ; 

__attribute__((used)) static bool smmu_pmu_events_compatible(struct perf_event *curr,
				       struct perf_event *new)
{
	if (new->pmu != curr->pmu)
		return false;

	if (to_smmu_pmu(new->pmu)->global_filter &&
	    !smmu_pmu_check_global_filter(curr, new))
		return false;

	return true;
}