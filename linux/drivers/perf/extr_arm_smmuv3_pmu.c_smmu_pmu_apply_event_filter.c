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
struct smmu_pmu {unsigned int num_counters; int /*<<< orphan*/ * events; int /*<<< orphan*/  used_counters; int /*<<< orphan*/  global_filter; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  SMMU_PMCG_DEFAULT_FILTER_SID ; 
 int /*<<< orphan*/  SMMU_PMCG_DEFAULT_FILTER_SPAN ; 
 int find_first_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  get_filter_enable (struct perf_event*) ; 
 int /*<<< orphan*/  get_filter_span (struct perf_event*) ; 
 int /*<<< orphan*/  get_filter_stream_id (struct perf_event*) ; 
 scalar_t__ smmu_pmu_check_global_filter (int /*<<< orphan*/ ,struct perf_event*) ; 
 int /*<<< orphan*/  smmu_pmu_set_event_filter (struct perf_event*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smmu_pmu_apply_event_filter(struct smmu_pmu *smmu_pmu,
				       struct perf_event *event, int idx)
{
	u32 span, sid;
	unsigned int num_ctrs = smmu_pmu->num_counters;
	bool filter_en = !!get_filter_enable(event);

	span = filter_en ? get_filter_span(event) :
			   SMMU_PMCG_DEFAULT_FILTER_SPAN;
	sid = filter_en ? get_filter_stream_id(event) :
			   SMMU_PMCG_DEFAULT_FILTER_SID;

	/* Support individual filter settings */
	if (!smmu_pmu->global_filter) {
		smmu_pmu_set_event_filter(event, idx, span, sid);
		return 0;
	}

	/* Requested settings same as current global settings*/
	idx = find_first_bit(smmu_pmu->used_counters, num_ctrs);
	if (idx == num_ctrs ||
	    smmu_pmu_check_global_filter(smmu_pmu->events[idx], event)) {
		smmu_pmu_set_event_filter(event, 0, span, sid);
		return 0;
	}

	return -EAGAIN;
}