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
struct lima_sched_task {int /*<<< orphan*/  last_dep; int /*<<< orphan*/  deps; } ;
struct drm_sched_job {int dummy; } ;
struct drm_sched_entity {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct lima_sched_task* to_lima_task (struct drm_sched_job*) ; 
 int /*<<< orphan*/  xa_empty (int /*<<< orphan*/ *) ; 
 struct dma_fence* xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dma_fence *lima_sched_dependency(struct drm_sched_job *job,
					       struct drm_sched_entity *entity)
{
	struct lima_sched_task *task = to_lima_task(job);

	if (!xa_empty(&task->deps))
		return xa_erase(&task->deps, task->last_dep++);

	return NULL;
}