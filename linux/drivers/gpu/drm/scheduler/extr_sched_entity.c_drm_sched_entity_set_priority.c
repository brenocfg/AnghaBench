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
struct drm_sched_entity {unsigned int num_rq_list; int /*<<< orphan*/  rq_lock; scalar_t__ rq; scalar_t__* rq_list; } ;
typedef  enum drm_sched_priority { ____Placeholder_drm_sched_priority } drm_sched_priority ;

/* Variables and functions */
 int /*<<< orphan*/  drm_sched_entity_set_rq_priority (scalar_t__*,int) ; 
 int /*<<< orphan*/  drm_sched_rq_add_entity (scalar_t__,struct drm_sched_entity*) ; 
 int /*<<< orphan*/  drm_sched_rq_remove_entity (scalar_t__,struct drm_sched_entity*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void drm_sched_entity_set_priority(struct drm_sched_entity *entity,
				   enum drm_sched_priority priority)
{
	unsigned int i;

	spin_lock(&entity->rq_lock);

	for (i = 0; i < entity->num_rq_list; ++i)
		drm_sched_entity_set_rq_priority(&entity->rq_list[i], priority);

	if (entity->rq) {
		drm_sched_rq_remove_entity(entity->rq, entity);
		drm_sched_entity_set_rq_priority(&entity->rq, priority);
		drm_sched_rq_add_entity(entity->rq, entity);
	}

	spin_unlock(&entity->rq_lock);
}