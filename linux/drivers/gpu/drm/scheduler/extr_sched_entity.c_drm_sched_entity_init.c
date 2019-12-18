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
struct drm_sched_entity {unsigned int num_rq_list; int /*<<< orphan*/  fence_context; int /*<<< orphan*/  fence_seq; int /*<<< orphan*/  job_queue; int /*<<< orphan*/  rq_lock; int /*<<< orphan*/ * last_scheduled; struct drm_sched_rq* rq; struct drm_sched_rq** rq_list; int /*<<< orphan*/ * guilty; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 struct drm_sched_rq** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct drm_sched_entity*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spsc_queue_init (int /*<<< orphan*/ *) ; 

int drm_sched_entity_init(struct drm_sched_entity *entity,
			  struct drm_sched_rq **rq_list,
			  unsigned int num_rq_list,
			  atomic_t *guilty)
{
	int i;

	if (!(entity && rq_list && (num_rq_list == 0 || rq_list[0])))
		return -EINVAL;

	memset(entity, 0, sizeof(struct drm_sched_entity));
	INIT_LIST_HEAD(&entity->list);
	entity->rq = NULL;
	entity->guilty = guilty;
	entity->num_rq_list = num_rq_list;
	entity->rq_list = kcalloc(num_rq_list, sizeof(struct drm_sched_rq *),
				GFP_KERNEL);
	if (!entity->rq_list)
		return -ENOMEM;

	for (i = 0; i < num_rq_list; ++i)
		entity->rq_list[i] = rq_list[i];

	if (num_rq_list)
		entity->rq = rq_list[0];

	entity->last_scheduled = NULL;

	spin_lock_init(&entity->rq_lock);
	spsc_queue_init(&entity->job_queue);

	atomic_set(&entity->fence_seq, 0);
	entity->fence_context = dma_fence_context_alloc(2);

	return 0;
}