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
struct TYPE_4__ {int type; size_t config; } ;
struct TYPE_3__ {int config; } ;
struct perf_event {TYPE_2__ attr; TYPE_1__ hw; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int ENOENT ; 
#define  PERF_TYPE_HARDWARE 130 
#define  PERF_TYPE_HW_CACHE 129 
#define  PERF_TYPE_RAW 128 
 int XTENSA_PMU_PMCTRL_INTEN ; 
 int XTENSA_PMU_PMCTRL_KRNLCNT ; 
 int XTENSA_PMU_PMCTRL_MASK ; 
 int XTENSA_PMU_PMCTRL_SELECT ; 
 int XTENSA_PMU_PMCTRL_SELECT_SHIFT ; 
 int XTENSA_PMU_PMCTRL_TRACELEVEL ; 
 int* xtensa_hw_ctl ; 
 int xtensa_pmu_cache_event (size_t) ; 

__attribute__((used)) static int xtensa_pmu_event_init(struct perf_event *event)
{
	int ret;

	switch (event->attr.type) {
	case PERF_TYPE_HARDWARE:
		if (event->attr.config >= ARRAY_SIZE(xtensa_hw_ctl) ||
		    xtensa_hw_ctl[event->attr.config] == 0)
			return -EINVAL;
		event->hw.config = xtensa_hw_ctl[event->attr.config];
		return 0;

	case PERF_TYPE_HW_CACHE:
		ret = xtensa_pmu_cache_event(event->attr.config);
		if (ret < 0)
			return ret;
		event->hw.config = ret;
		return 0;

	case PERF_TYPE_RAW:
		/* Not 'previous counter' select */
		if ((event->attr.config & XTENSA_PMU_PMCTRL_SELECT) ==
		    (1 << XTENSA_PMU_PMCTRL_SELECT_SHIFT))
			return -EINVAL;
		event->hw.config = (event->attr.config &
				    (XTENSA_PMU_PMCTRL_KRNLCNT |
				     XTENSA_PMU_PMCTRL_TRACELEVEL |
				     XTENSA_PMU_PMCTRL_SELECT |
				     XTENSA_PMU_PMCTRL_MASK)) |
			XTENSA_PMU_PMCTRL_INTEN;
		return 0;

	default:
		return -ENOENT;
	}
}