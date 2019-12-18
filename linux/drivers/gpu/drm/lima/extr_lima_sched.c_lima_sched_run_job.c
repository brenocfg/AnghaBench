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
struct lima_vm {int dummy; } ;
struct lima_sched_task {struct dma_fence* fence; struct lima_vm* vm; } ;
struct lima_sched_pipe {int num_l2_cache; int num_mmu; int error; int /*<<< orphan*/  (* task_run ) (struct lima_sched_pipe*,struct lima_sched_task*) ;scalar_t__* mmu; scalar_t__ bcast_mmu; struct lima_vm* current_vm; int /*<<< orphan*/ * l2_cache; struct lima_sched_task* current_task; } ;
struct dma_fence {int dummy; } ;
struct lima_fence {struct dma_fence base; } ;
struct drm_sched_job {TYPE_2__* s_fence; int /*<<< orphan*/  sched; } ;
struct TYPE_3__ {scalar_t__ error; } ;
struct TYPE_4__ {TYPE_1__ finished; } ;

/* Variables and functions */
 struct dma_fence* dma_fence_get (struct dma_fence*) ; 
 struct lima_fence* lima_fence_create (struct lima_sched_pipe*) ; 
 int /*<<< orphan*/  lima_l2_cache_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lima_mmu_switch_vm (scalar_t__,struct lima_vm*) ; 
 struct lima_vm* lima_vm_get (struct lima_vm*) ; 
 int /*<<< orphan*/  lima_vm_put (struct lima_vm*) ; 
 int /*<<< orphan*/  stub1 (struct lima_sched_pipe*,struct lima_sched_task*) ; 
 struct lima_sched_pipe* to_lima_pipe (int /*<<< orphan*/ ) ; 
 struct lima_sched_task* to_lima_task (struct drm_sched_job*) ; 

__attribute__((used)) static struct dma_fence *lima_sched_run_job(struct drm_sched_job *job)
{
	struct lima_sched_task *task = to_lima_task(job);
	struct lima_sched_pipe *pipe = to_lima_pipe(job->sched);
	struct lima_fence *fence;
	struct dma_fence *ret;
	struct lima_vm *vm = NULL, *last_vm = NULL;
	int i;

	/* after GPU reset */
	if (job->s_fence->finished.error < 0)
		return NULL;

	fence = lima_fence_create(pipe);
	if (!fence)
		return NULL;
	task->fence = &fence->base;

	/* for caller usage of the fence, otherwise irq handler
	 * may consume the fence before caller use it
	 */
	ret = dma_fence_get(task->fence);

	pipe->current_task = task;

	/* this is needed for MMU to work correctly, otherwise GP/PP
	 * will hang or page fault for unknown reason after running for
	 * a while.
	 *
	 * Need to investigate:
	 * 1. is it related to TLB
	 * 2. how much performance will be affected by L2 cache flush
	 * 3. can we reduce the calling of this function because all
	 *    GP/PP use the same L2 cache on mali400
	 *
	 * TODO:
	 * 1. move this to task fini to save some wait time?
	 * 2. when GP/PP use different l2 cache, need PP wait GP l2
	 *    cache flush?
	 */
	for (i = 0; i < pipe->num_l2_cache; i++)
		lima_l2_cache_flush(pipe->l2_cache[i]);

	if (task->vm != pipe->current_vm) {
		vm = lima_vm_get(task->vm);
		last_vm = pipe->current_vm;
		pipe->current_vm = task->vm;
	}

	if (pipe->bcast_mmu)
		lima_mmu_switch_vm(pipe->bcast_mmu, vm);
	else {
		for (i = 0; i < pipe->num_mmu; i++)
			lima_mmu_switch_vm(pipe->mmu[i], vm);
	}

	if (last_vm)
		lima_vm_put(last_vm);

	pipe->error = false;
	pipe->task_run(pipe, task);

	return task->fence;
}