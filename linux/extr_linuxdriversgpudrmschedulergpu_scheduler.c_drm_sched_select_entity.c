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
struct drm_sched_entity {int dummy; } ;
struct drm_gpu_scheduler {int /*<<< orphan*/ * sched_rq; } ;

/* Variables and functions */
 int DRM_SCHED_PRIORITY_MAX ; 
 int DRM_SCHED_PRIORITY_MIN ; 
 int /*<<< orphan*/  drm_sched_ready (struct drm_gpu_scheduler*) ; 
 struct drm_sched_entity* drm_sched_rq_select_entity (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_sched_entity *
drm_sched_select_entity(struct drm_gpu_scheduler *sched)
{
	struct drm_sched_entity *entity;
	int i;

	if (!drm_sched_ready(sched))
		return NULL;

	/* Kernel run queue has higher priority than normal run queue*/
	for (i = DRM_SCHED_PRIORITY_MAX - 1; i >= DRM_SCHED_PRIORITY_MIN; i--) {
		entity = drm_sched_rq_select_entity(&sched->sched_rq[i]);
		if (entity)
			break;
	}

	return entity;
}