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
struct TYPE_2__ {int /*<<< orphan*/  current_vgpu; struct gvt_sched_data* sched_data; } ;
struct intel_gvt {int /*<<< orphan*/  sched_lock; TYPE_1__ scheduler; int /*<<< orphan*/  service_request; } ;
struct gvt_sched_data {scalar_t__ expire_time; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  GVT_TS_BALANCE_PERIOD_MS ; 
 int /*<<< orphan*/  INTEL_GVT_REQUEST_EVENT_SCHED ; 
 int /*<<< orphan*/  INTEL_GVT_REQUEST_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gvt_balance_timeslice (struct gvt_sched_data*) ; 
 scalar_t__ ktime_add_ms (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tbs_sched_func (struct gvt_sched_data*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vgpu_update_timeslice (int /*<<< orphan*/ ,scalar_t__) ; 

void intel_gvt_schedule(struct intel_gvt *gvt)
{
	struct gvt_sched_data *sched_data = gvt->scheduler.sched_data;
	ktime_t cur_time;

	mutex_lock(&gvt->sched_lock);
	cur_time = ktime_get();

	if (test_and_clear_bit(INTEL_GVT_REQUEST_SCHED,
				(void *)&gvt->service_request)) {
		if (cur_time >= sched_data->expire_time) {
			gvt_balance_timeslice(sched_data);
			sched_data->expire_time = ktime_add_ms(
				cur_time, GVT_TS_BALANCE_PERIOD_MS);
		}
	}
	clear_bit(INTEL_GVT_REQUEST_EVENT_SCHED, (void *)&gvt->service_request);

	vgpu_update_timeslice(gvt->scheduler.current_vgpu, cur_time);
	tbs_sched_func(sched_data);

	mutex_unlock(&gvt->sched_lock);
}