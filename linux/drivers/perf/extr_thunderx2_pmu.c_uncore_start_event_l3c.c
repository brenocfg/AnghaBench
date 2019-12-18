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
struct hw_perf_event {int /*<<< orphan*/  event_base; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  config_base; } ;
struct perf_event {struct hw_perf_event hw; } ;

/* Variables and functions */
 int GET_EVENTID (struct perf_event*) ; 
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uncore_start_event_l3c(struct perf_event *event, int flags)
{
	u32 val;
	struct hw_perf_event *hwc = &event->hw;

	/* event id encoded in bits [07:03] */
	val = GET_EVENTID(event) << 3;
	reg_writel(val, hwc->config_base);
	local64_set(&hwc->prev_count, 0);
	reg_writel(0, hwc->event_base);
}