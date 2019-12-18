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
struct hw_perf_event {scalar_t__ config_base; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cluster_pmu {int /*<<< orphan*/  used_groups; int /*<<< orphan*/  used_counters; TYPE_1__* l2cache_pmu; } ;
struct TYPE_2__ {int num_counters; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ L2CYCLE_CTR_RAW_CODE ; 
 unsigned int L2_EVT_GROUP (scalar_t__) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int l2_cycle_ctr_idx ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2_cache_get_event_idx(struct cluster_pmu *cluster,
				   struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	int idx;
	int num_ctrs = cluster->l2cache_pmu->num_counters - 1;
	unsigned int group;

	if (hwc->config_base == L2CYCLE_CTR_RAW_CODE) {
		if (test_and_set_bit(l2_cycle_ctr_idx, cluster->used_counters))
			return -EAGAIN;

		return l2_cycle_ctr_idx;
	}

	idx = find_first_zero_bit(cluster->used_counters, num_ctrs);
	if (idx == num_ctrs)
		/* The counters are all in use. */
		return -EAGAIN;

	/*
	 * Check for column exclusion: event column already in use by another
	 * event. This is for events which are not in the same group.
	 * Conflicting events in the same group are detected in event_init.
	 */
	group = L2_EVT_GROUP(hwc->config_base);
	if (test_bit(group, cluster->used_groups))
		return -EAGAIN;

	set_bit(idx, cluster->used_counters);
	set_bit(group, cluster->used_groups);

	return idx;
}