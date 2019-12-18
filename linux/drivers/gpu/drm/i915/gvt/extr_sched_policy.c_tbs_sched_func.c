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
struct vgpu_sched_data {int /*<<< orphan*/  lru_list; int /*<<< orphan*/  pri_sched; } ;
struct intel_vgpu {struct vgpu_sched_data* sched_data; } ;
struct intel_gvt_workload_scheduler {struct intel_vgpu* next_vgpu; } ;
struct intel_gvt {struct intel_vgpu* idle_vgpu; struct intel_gvt_workload_scheduler scheduler; } ;
struct gvt_sched_data {int /*<<< orphan*/  lru_runq_head; struct intel_gvt* gvt; } ;

/* Variables and functions */
 struct intel_vgpu* find_busy_vgpu (struct gvt_sched_data*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_schedule_next_vgpu (struct intel_gvt*) ; 

__attribute__((used)) static void tbs_sched_func(struct gvt_sched_data *sched_data)
{
	struct intel_gvt *gvt = sched_data->gvt;
	struct intel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	struct vgpu_sched_data *vgpu_data;
	struct intel_vgpu *vgpu = NULL;

	/* no active vgpu or has already had a target */
	if (list_empty(&sched_data->lru_runq_head) || scheduler->next_vgpu)
		goto out;

	vgpu = find_busy_vgpu(sched_data);
	if (vgpu) {
		scheduler->next_vgpu = vgpu;
		vgpu_data = vgpu->sched_data;
		if (!vgpu_data->pri_sched) {
			/* Move the last used vGPU to the tail of lru_list */
			list_del_init(&vgpu_data->lru_list);
			list_add_tail(&vgpu_data->lru_list,
				      &sched_data->lru_runq_head);
		}
	} else {
		scheduler->next_vgpu = gvt->idle_vgpu;
	}
out:
	if (scheduler->next_vgpu)
		try_to_schedule_next_vgpu(gvt);
}