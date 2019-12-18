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
struct TYPE_4__ {TYPE_1__* s_fence; } ;
struct lima_sched_task {TYPE_2__ base; } ;
struct lima_sched_context {int /*<<< orphan*/  base; } ;
struct dma_fence {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  finished; } ;

/* Variables and functions */
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_sched_entity_push_job (TYPE_2__*,int /*<<< orphan*/ *) ; 

struct dma_fence *lima_sched_context_queue_task(struct lima_sched_context *context,
						struct lima_sched_task *task)
{
	struct dma_fence *fence = dma_fence_get(&task->base.s_fence->finished);

	drm_sched_entity_push_job(&task->base, &context->base);
	return fence;
}