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
struct smmu_pmu {unsigned int num_counters; int /*<<< orphan*/  used_counters; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int smmu_pmu_apply_event_filter (struct smmu_pmu*,struct perf_event*,int) ; 

__attribute__((used)) static int smmu_pmu_get_event_idx(struct smmu_pmu *smmu_pmu,
				  struct perf_event *event)
{
	int idx, err;
	unsigned int num_ctrs = smmu_pmu->num_counters;

	idx = find_first_zero_bit(smmu_pmu->used_counters, num_ctrs);
	if (idx == num_ctrs)
		/* The counters are all in use. */
		return -EAGAIN;

	err = smmu_pmu_apply_event_filter(smmu_pmu, event, idx);
	if (err)
		return err;

	set_bit(idx, smmu_pmu->used_counters);

	return idx;
}