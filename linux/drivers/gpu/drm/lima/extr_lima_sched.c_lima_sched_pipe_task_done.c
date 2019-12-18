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
struct lima_sched_task {int /*<<< orphan*/  fence; } ;
struct lima_sched_pipe {int /*<<< orphan*/  (* task_fini ) (struct lima_sched_pipe*) ;struct lima_sched_task* current_task; int /*<<< orphan*/  error_work; scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct lima_sched_pipe*) ; 

void lima_sched_pipe_task_done(struct lima_sched_pipe *pipe)
{
	if (pipe->error)
		schedule_work(&pipe->error_work);
	else {
		struct lima_sched_task *task = pipe->current_task;

		pipe->task_fini(pipe);
		dma_fence_signal(task->fence);
	}
}