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
struct TYPE_2__ {int type; int /*<<< orphan*/  config; } ;
struct perf_event {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTLB_LOAD_MISS ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ITLB_LOAD_MISS ; 
 int PERF_8xx_ID_CPU_CYCLES ; 
 int PERF_8xx_ID_DTLB_LOAD_MISS ; 
 int PERF_8xx_ID_HW_INSTRUCTIONS ; 
 int PERF_8xx_ID_ITLB_LOAD_MISS ; 
 int /*<<< orphan*/  PERF_COUNT_HW_CPU_CYCLES ; 
 int /*<<< orphan*/  PERF_COUNT_HW_INSTRUCTIONS ; 
#define  PERF_TYPE_HARDWARE 130 
#define  PERF_TYPE_HW_CACHE 129 
#define  PERF_TYPE_RAW 128 

__attribute__((used)) static int event_type(struct perf_event *event)
{
	switch (event->attr.type) {
	case PERF_TYPE_HARDWARE:
		if (event->attr.config == PERF_COUNT_HW_CPU_CYCLES)
			return PERF_8xx_ID_CPU_CYCLES;
		if (event->attr.config == PERF_COUNT_HW_INSTRUCTIONS)
			return PERF_8xx_ID_HW_INSTRUCTIONS;
		break;
	case PERF_TYPE_HW_CACHE:
		if (event->attr.config == ITLB_LOAD_MISS)
			return PERF_8xx_ID_ITLB_LOAD_MISS;
		if (event->attr.config == DTLB_LOAD_MISS)
			return PERF_8xx_ID_DTLB_LOAD_MISS;
		break;
	case PERF_TYPE_RAW:
		break;
	default:
		return -ENOENT;
	}
	return -EOPNOTSUPP;
}