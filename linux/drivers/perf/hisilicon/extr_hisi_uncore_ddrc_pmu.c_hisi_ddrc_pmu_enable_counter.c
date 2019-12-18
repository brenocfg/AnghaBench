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
struct hw_perf_event {int dummy; } ;
struct hisi_pmu {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DDRC_EVENT_CTRL ; 
 int GET_DDRC_EVENTID (struct hw_perf_event*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hisi_ddrc_pmu_enable_counter(struct hisi_pmu *ddrc_pmu,
					 struct hw_perf_event *hwc)
{
	u32 val;

	/* Set counter index(event code) in DDRC_EVENT_CTRL register */
	val = readl(ddrc_pmu->base + DDRC_EVENT_CTRL);
	val |= (1 << GET_DDRC_EVENTID(hwc));
	writel(val, ddrc_pmu->base + DDRC_EVENT_CTRL);
}