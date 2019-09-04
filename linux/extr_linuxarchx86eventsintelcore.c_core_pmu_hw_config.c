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
struct perf_event {int dummy; } ;

/* Variables and functions */
 int intel_pmu_bts_config (struct perf_event*) ; 
 int x86_pmu_hw_config (struct perf_event*) ; 

__attribute__((used)) static int core_pmu_hw_config(struct perf_event *event)
{
	int ret = x86_pmu_hw_config(event);

	if (ret)
		return ret;

	return intel_pmu_bts_config(event);
}