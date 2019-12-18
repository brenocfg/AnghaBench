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
struct hw_perf_event {scalar_t__ state; int /*<<< orphan*/  idx; int /*<<< orphan*/  prev_count; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct arm_ccn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_ccn_pmu_read_counter (struct arm_ccn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_ccn_pmu_xp_dt_config (struct perf_event*,int) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct arm_ccn* pmu_to_arm_ccn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arm_ccn_pmu_event_start(struct perf_event *event, int flags)
{
	struct arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	struct hw_perf_event *hw = &event->hw;

	local64_set(&event->hw.prev_count,
			arm_ccn_pmu_read_counter(ccn, hw->idx));
	hw->state = 0;

	/* Set the DT bus input, engaging the counter */
	arm_ccn_pmu_xp_dt_config(event, 1);
}