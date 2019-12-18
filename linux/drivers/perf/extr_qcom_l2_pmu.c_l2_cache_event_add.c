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
struct hw_perf_event {int idx; int state; int /*<<< orphan*/  prev_count; } ;
struct perf_event {int /*<<< orphan*/  cpu; int /*<<< orphan*/  pmu; struct hw_perf_event hw; } ;
struct cluster_pmu {struct perf_event** events; } ;

/* Variables and functions */
 int PERF_EF_START ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 struct cluster_pmu* get_cluster_pmu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2_cache_event_start (struct perf_event*,int) ; 
 int l2_cache_get_event_idx (struct cluster_pmu*,struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 
 int /*<<< orphan*/  to_l2cache_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2_cache_event_add(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	int idx;
	int err = 0;
	struct cluster_pmu *cluster;

	cluster = get_cluster_pmu(to_l2cache_pmu(event->pmu), event->cpu);

	idx = l2_cache_get_event_idx(cluster, event);
	if (idx < 0)
		return idx;

	hwc->idx = idx;
	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	cluster->events[idx] = event;
	local64_set(&hwc->prev_count, 0);

	if (flags & PERF_EF_START)
		l2_cache_event_start(event, flags);

	/* Propagate changes to the userspace mapping. */
	perf_event_update_userpage(event);

	return err;
}