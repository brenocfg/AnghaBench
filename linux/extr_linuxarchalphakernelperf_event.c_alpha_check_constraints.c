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
struct perf_event {int dummy; } ;
struct TYPE_2__ {int num_pmcs; int (* check_constraints ) (struct perf_event**,unsigned long*,int) ;} ;

/* Variables and functions */
 TYPE_1__* alpha_pmu ; 
 int stub1 (struct perf_event**,unsigned long*,int) ; 

__attribute__((used)) static int alpha_check_constraints(struct perf_event **events,
				   unsigned long *evtypes, int n_ev)
{

	/* No HW events is possible from hw_perf_group_sched_in(). */
	if (n_ev == 0)
		return 0;

	if (n_ev > alpha_pmu->num_pmcs)
		return -1;

	return alpha_pmu->check_constraints(events, evtypes, n_ev);
}