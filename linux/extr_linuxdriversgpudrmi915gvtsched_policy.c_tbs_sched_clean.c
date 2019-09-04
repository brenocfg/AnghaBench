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
struct intel_gvt_workload_scheduler {struct gvt_sched_data* sched_data; } ;
struct intel_gvt {struct intel_gvt_workload_scheduler scheduler; } ;
struct gvt_sched_data {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct gvt_sched_data*) ; 

__attribute__((used)) static void tbs_sched_clean(struct intel_gvt *gvt)
{
	struct intel_gvt_workload_scheduler *scheduler =
		&gvt->scheduler;
	struct gvt_sched_data *data = scheduler->sched_data;

	hrtimer_cancel(&data->timer);

	kfree(data);
	scheduler->sched_data = NULL;
}