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
struct lima_vm {int dummy; } ;
struct lima_sched_task {int num_bos; int /*<<< orphan*/  fence; struct lima_bo** bos; struct lima_vm* vm; } ;
struct lima_sched_pipe {int /*<<< orphan*/  task_slab; } ;
struct lima_bo {int dummy; } ;
struct drm_sched_job {int /*<<< orphan*/  sched; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct lima_sched_task*) ; 
 int /*<<< orphan*/  lima_sched_task_fini (struct lima_sched_task*) ; 
 int /*<<< orphan*/  lima_vm_bo_del (struct lima_vm*,struct lima_bo*) ; 
 struct lima_sched_pipe* to_lima_pipe (int /*<<< orphan*/ ) ; 
 struct lima_sched_task* to_lima_task (struct drm_sched_job*) ; 

__attribute__((used)) static void lima_sched_free_job(struct drm_sched_job *job)
{
	struct lima_sched_task *task = to_lima_task(job);
	struct lima_sched_pipe *pipe = to_lima_pipe(job->sched);
	struct lima_vm *vm = task->vm;
	struct lima_bo **bos = task->bos;
	int i;

	dma_fence_put(task->fence);

	for (i = 0; i < task->num_bos; i++)
		lima_vm_bo_del(vm, bos[i]);

	lima_sched_task_fini(task);
	kmem_cache_free(pipe->task_slab, task);
}