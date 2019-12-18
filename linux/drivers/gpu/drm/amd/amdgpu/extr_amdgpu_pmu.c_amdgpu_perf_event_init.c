#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  config; } ;
struct hw_perf_event {int /*<<< orphan*/  conf; } ;
struct perf_event {TYPE_2__ attr; TYPE_1__* pmu; struct hw_perf_event hw; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int amdgpu_perf_event_init(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;

	/* test the event attr type check for PMU enumeration */
	if (event->attr.type != event->pmu->type)
		return -ENOENT;

	/* update the hw_perf_event struct with config data */
	hwc->conf = event->attr.config;

	return 0;
}