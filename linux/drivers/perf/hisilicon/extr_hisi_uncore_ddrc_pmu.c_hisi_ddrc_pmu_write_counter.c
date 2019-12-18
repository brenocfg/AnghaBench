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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hw_perf_event {int dummy; } ;
struct hisi_pmu {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_DDRC_EVENTID (struct hw_perf_event*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ hisi_ddrc_pmu_get_counter_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_uncore_pmu_counter_valid (struct hisi_pmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hisi_ddrc_pmu_write_counter(struct hisi_pmu *ddrc_pmu,
					struct hw_perf_event *hwc, u64 val)
{
	u32 idx = GET_DDRC_EVENTID(hwc);

	if (!hisi_uncore_pmu_counter_valid(ddrc_pmu, idx)) {
		dev_err(ddrc_pmu->dev, "Unsupported event index:%d!\n", idx);
		return;
	}

	writel((u32)val,
	       ddrc_pmu->base + hisi_ddrc_pmu_get_counter_offset(idx));
}