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
struct intel_vgpu_submission {int /*<<< orphan*/  running_workload_num; } ;
struct intel_vgpu {struct intel_gvt* gvt; struct intel_vgpu_submission submission; } ;
struct intel_gvt_workload_scheduler {int /*<<< orphan*/  workload_complete_wq; } ;
struct intel_gvt {struct intel_gvt_workload_scheduler scheduler; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gvt_dbg_sched (char*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void intel_gvt_wait_vgpu_idle(struct intel_vgpu *vgpu)
{
	struct intel_vgpu_submission *s = &vgpu->submission;
	struct intel_gvt *gvt = vgpu->gvt;
	struct intel_gvt_workload_scheduler *scheduler = &gvt->scheduler;

	if (atomic_read(&s->running_workload_num)) {
		gvt_dbg_sched("wait vgpu idle\n");

		wait_event(scheduler->workload_complete_wq,
				!atomic_read(&s->running_workload_num));
	}
}