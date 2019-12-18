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
struct lima_sched_task {int /*<<< orphan*/  base; } ;
struct lima_sched_pipe {int num_mmu; int /*<<< orphan*/  base; int /*<<< orphan*/ * current_task; int /*<<< orphan*/ * current_vm; scalar_t__* mmu; scalar_t__ bcast_mmu; int /*<<< orphan*/  (* task_error ) (struct lima_sched_pipe*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_sched_increase_karma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_resubmit_jobs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_start (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_sched_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lima_mmu_page_fault_resume (scalar_t__) ; 
 int /*<<< orphan*/  lima_vm_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct lima_sched_pipe*) ; 

__attribute__((used)) static void lima_sched_handle_error_task(struct lima_sched_pipe *pipe,
					 struct lima_sched_task *task)
{
	drm_sched_stop(&pipe->base, &task->base);

	if (task)
		drm_sched_increase_karma(&task->base);

	pipe->task_error(pipe);

	if (pipe->bcast_mmu)
		lima_mmu_page_fault_resume(pipe->bcast_mmu);
	else {
		int i;

		for (i = 0; i < pipe->num_mmu; i++)
			lima_mmu_page_fault_resume(pipe->mmu[i]);
	}

	if (pipe->current_vm)
		lima_vm_put(pipe->current_vm);

	pipe->current_vm = NULL;
	pipe->current_task = NULL;

	drm_sched_resubmit_jobs(&pipe->base);
	drm_sched_start(&pipe->base, true);
}