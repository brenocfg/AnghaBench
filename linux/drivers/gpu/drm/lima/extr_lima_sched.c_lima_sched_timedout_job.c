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
struct lima_sched_task {int dummy; } ;
struct lima_sched_pipe {int dummy; } ;
struct drm_sched_job {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  lima_sched_handle_error_task (struct lima_sched_pipe*,struct lima_sched_task*) ; 
 struct lima_sched_pipe* to_lima_pipe (int /*<<< orphan*/ ) ; 
 struct lima_sched_task* to_lima_task (struct drm_sched_job*) ; 

__attribute__((used)) static void lima_sched_timedout_job(struct drm_sched_job *job)
{
	struct lima_sched_pipe *pipe = to_lima_pipe(job->sched);
	struct lima_sched_task *task = to_lima_task(job);

	DRM_ERROR("lima job timeout\n");

	lima_sched_handle_error_task(pipe, task);
}