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

/* Variables and functions */
 int /*<<< orphan*/  PMU_BATTERY_STATE ; 
 scalar_t__ PMU_OHARE_BASED ; 
 int /*<<< orphan*/  PMU_SMART_BATTERY_STATE ; 
 int /*<<< orphan*/  async_req_locks ; 
 int /*<<< orphan*/  batt_req ; 
 int /*<<< orphan*/  done_battery_state_ohare ; 
 int /*<<< orphan*/  done_battery_state_smart ; 
 scalar_t__ pmu_cur_battery ; 
 scalar_t__ pmu_kind ; 
 int /*<<< orphan*/  pmu_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
query_battery_state(void)
{
	if (test_and_set_bit(0, &async_req_locks))
		return;
	if (pmu_kind == PMU_OHARE_BASED)
		pmu_request(&batt_req, done_battery_state_ohare,
			1, PMU_BATTERY_STATE);
	else
		pmu_request(&batt_req, done_battery_state_smart,
			2, PMU_SMART_BATTERY_STATE, pmu_cur_battery+1);
}