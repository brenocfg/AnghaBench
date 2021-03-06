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
struct hw_perf_event {scalar_t__ state; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct l3cache_event_ops {int /*<<< orphan*/  (* start ) (struct perf_event*) ;} ;

/* Variables and functions */
 struct l3cache_event_ops* l3cache_event_get_ops (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 

__attribute__((used)) static void qcom_l3_cache__event_start(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	const struct l3cache_event_ops *ops = l3cache_event_get_ops(event);

	hwc->state = 0;
	ops->start(event);
}