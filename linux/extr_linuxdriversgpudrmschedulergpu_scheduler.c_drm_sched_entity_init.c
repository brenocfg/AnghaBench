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
struct drm_sched_rq {int dummy; } ;
struct drm_sched_entity {int /*<<< orphan*/  fence_context; int /*<<< orphan*/  fence_seq; int /*<<< orphan*/  job_queue; int /*<<< orphan*/  rq_lock; int /*<<< orphan*/ * last_scheduled; int /*<<< orphan*/ * guilty; struct drm_sched_rq* rq; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  memset (struct drm_sched_entity*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spsc_queue_init (int /*<<< orphan*/ *) ; 

int drm_sched_entity_init(struct drm_sched_entity *entity,
			  struct drm_sched_rq **rq_list,
			  unsigned int num_rq_list,
			  atomic_t *guilty)
{
	if (!(entity && rq_list && num_rq_list > 0 && rq_list[0]))
		return -EINVAL;

	memset(entity, 0, sizeof(struct drm_sched_entity));
	INIT_LIST_HEAD(&entity->list);
	entity->rq = rq_list[0];
	entity->guilty = guilty;
	entity->last_scheduled = NULL;

	spin_lock_init(&entity->rq_lock);
	spsc_queue_init(&entity->job_queue);

	atomic_set(&entity->fence_seq, 0);
	entity->fence_context = dma_fence_context_alloc(2);

	return 0;
}