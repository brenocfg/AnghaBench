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
struct smmu_pmu {int dummy; } ;
struct perf_event {int /*<<< orphan*/  pmu; } ;

/* Variables and functions */
 int SMMU_PMCG_SID_SPAN_SHIFT ; 
 int get_event (struct perf_event*) ; 
 int /*<<< orphan*/  smmu_pmu_set_evtyper (struct smmu_pmu*,int,int) ; 
 int /*<<< orphan*/  smmu_pmu_set_smr (struct smmu_pmu*,int,int) ; 
 struct smmu_pmu* to_smmu_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smmu_pmu_set_event_filter(struct perf_event *event,
				      int idx, u32 span, u32 sid)
{
	struct smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	u32 evtyper;

	evtyper = get_event(event) | span << SMMU_PMCG_SID_SPAN_SHIFT;
	smmu_pmu_set_evtyper(smmu_pmu, idx, evtyper);
	smmu_pmu_set_smr(smmu_pmu, idx, sid);
}