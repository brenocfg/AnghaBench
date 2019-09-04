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
typedef  scalar_t__ u64 ;
struct debug_store {scalar_t__ pebs_interrupt_threshold; scalar_t__ pebs_buffer_base; scalar_t__ pebs_absolute_maximum; } ;
struct cpu_hw_events {scalar_t__ n_pebs; scalar_t__ n_large_pebs; struct debug_store* ds; } ;
struct TYPE_2__ {int flags; int max_pebs_events; int num_counters_fixed; int pebs_record_size; } ;

/* Variables and functions */
 int PMU_FL_PEBS_ALL ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static inline void pebs_update_threshold(struct cpu_hw_events *cpuc)
{
	struct debug_store *ds = cpuc->ds;
	u64 threshold;
	int reserved;

	if (x86_pmu.flags & PMU_FL_PEBS_ALL)
		reserved = x86_pmu.max_pebs_events + x86_pmu.num_counters_fixed;
	else
		reserved = x86_pmu.max_pebs_events;

	if (cpuc->n_pebs == cpuc->n_large_pebs) {
		threshold = ds->pebs_absolute_maximum -
			reserved * x86_pmu.pebs_record_size;
	} else {
		threshold = ds->pebs_buffer_base + x86_pmu.pebs_record_size;
	}

	ds->pebs_interrupt_threshold = threshold;
}