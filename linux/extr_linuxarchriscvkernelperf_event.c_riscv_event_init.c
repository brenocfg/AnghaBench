#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct perf_event_attr {int type; int /*<<< orphan*/  config; } ;
struct hw_perf_event {int config; int idx; } ;
struct perf_event {int /*<<< orphan*/  (* destroy ) (struct perf_event*) ;struct perf_event_attr attr; struct hw_perf_event hw; } ;
struct TYPE_2__ {int (* map_hw_event ) (int /*<<< orphan*/ ) ;int (* map_cache_event ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  PERF_TYPE_HARDWARE 130 
#define  PERF_TYPE_HW_CACHE 129 
#define  PERF_TYPE_RAW 128 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int reserve_pmc_hardware () ; 
 int /*<<< orphan*/  riscv_active_events ; 
 int /*<<< orphan*/  riscv_event_destroy (struct perf_event*) ; 
 TYPE_1__* riscv_pmu ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct perf_event*) ; 

__attribute__((used)) static int riscv_event_init(struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	struct hw_perf_event *hwc = &event->hw;
	int err;
	int code;

	if (atomic_inc_return(&riscv_active_events) == 1) {
		err = reserve_pmc_hardware();

		if (err) {
			pr_warn("PMC hardware not available\n");
			atomic_dec(&riscv_active_events);
			return -EBUSY;
		}
	}

	switch (event->attr.type) {
	case PERF_TYPE_HARDWARE:
		code = riscv_pmu->map_hw_event(attr->config);
		break;
	case PERF_TYPE_HW_CACHE:
		code = riscv_pmu->map_cache_event(attr->config);
		break;
	case PERF_TYPE_RAW:
		return -EOPNOTSUPP;
	default:
		return -ENOENT;
	}

	event->destroy = riscv_event_destroy;
	if (code < 0) {
		event->destroy(event);
		return code;
	}

	/*
	 * idx is set to -1 because the index of a general event should not be
	 * decided until binding to some counter in pmu->add().
	 *
	 * But since we don't have such support, later in pmu->add(), we just
	 * use hwc->config as the index instead.
	 */
	hwc->config = code;
	hwc->idx = -1;

	return 0;
}