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
struct hw_perf_event {int state; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct TYPE_4__ {TYPE_1__* pmu; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read ) (struct perf_event*) ;} ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 TYPE_2__* riscv_pmu ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 

__attribute__((used)) static void riscv_pmu_stop(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;

	WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
	hwc->state |= PERF_HES_STOPPED;

	if ((flags & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) {
		riscv_pmu->pmu->read(event);
		hwc->state |= PERF_HES_UPTODATE;
	}
}