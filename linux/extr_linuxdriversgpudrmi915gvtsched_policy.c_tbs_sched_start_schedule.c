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
struct vgpu_sched_data {int pri_sched; int active; int /*<<< orphan*/  lru_list; int /*<<< orphan*/  pri_time; } ;
struct intel_vgpu {struct vgpu_sched_data* sched_data; TYPE_1__* gvt; } ;
struct gvt_sched_data {int /*<<< orphan*/  period; int /*<<< orphan*/  timer; int /*<<< orphan*/  lru_runq_head; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {struct gvt_sched_data* sched_data; } ;
struct TYPE_3__ {TYPE_2__ scheduler; } ;

/* Variables and functions */
 int /*<<< orphan*/  GVT_SCHED_VGPU_PRI_TIME ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tbs_sched_start_schedule(struct intel_vgpu *vgpu)
{
	struct gvt_sched_data *sched_data = vgpu->gvt->scheduler.sched_data;
	struct vgpu_sched_data *vgpu_data = vgpu->sched_data;
	ktime_t now;

	if (!list_empty(&vgpu_data->lru_list))
		return;

	now = ktime_get();
	vgpu_data->pri_time = ktime_add(now,
					ktime_set(GVT_SCHED_VGPU_PRI_TIME, 0));
	vgpu_data->pri_sched = true;

	list_add(&vgpu_data->lru_list, &sched_data->lru_runq_head);

	if (!hrtimer_active(&sched_data->timer))
		hrtimer_start(&sched_data->timer, ktime_add_ns(ktime_get(),
			sched_data->period), HRTIMER_MODE_ABS);
	vgpu_data->active = true;
}