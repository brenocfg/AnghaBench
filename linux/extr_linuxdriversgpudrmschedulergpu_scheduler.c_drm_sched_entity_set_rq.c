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
struct drm_sched_entity {int /*<<< orphan*/  rq_lock; struct drm_sched_rq* rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  drm_sched_rq_add_entity (struct drm_sched_rq*,struct drm_sched_entity*) ; 
 int /*<<< orphan*/  drm_sched_rq_remove_entity (struct drm_sched_rq*,struct drm_sched_entity*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void drm_sched_entity_set_rq(struct drm_sched_entity *entity,
			     struct drm_sched_rq *rq)
{
	if (entity->rq == rq)
		return;

	BUG_ON(!rq);

	spin_lock(&entity->rq_lock);
	drm_sched_rq_remove_entity(entity->rq, entity);
	entity->rq = rq;
	drm_sched_rq_add_entity(rq, entity);
	spin_unlock(&entity->rq_lock);
}