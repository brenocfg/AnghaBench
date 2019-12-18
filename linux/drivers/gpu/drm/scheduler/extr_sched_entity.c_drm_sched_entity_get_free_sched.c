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
struct drm_sched_rq {struct drm_gpu_scheduler* sched; } ;
struct drm_sched_entity {int num_rq_list; struct drm_sched_rq** rq_list; } ;
struct drm_gpu_scheduler {int /*<<< orphan*/  num_jobs; int /*<<< orphan*/  name; int /*<<< orphan*/  ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARN (char*,int /*<<< orphan*/ ) ; 
 unsigned int UINT_MAX ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_sched_rq *
drm_sched_entity_get_free_sched(struct drm_sched_entity *entity)
{
	struct drm_sched_rq *rq = NULL;
	unsigned int min_jobs = UINT_MAX, num_jobs;
	int i;

	for (i = 0; i < entity->num_rq_list; ++i) {
		struct drm_gpu_scheduler *sched = entity->rq_list[i]->sched;

		if (!entity->rq_list[i]->sched->ready) {
			DRM_WARN("sched%s is not ready, skipping", sched->name);
			continue;
		}

		num_jobs = atomic_read(&sched->num_jobs);
		if (num_jobs < min_jobs) {
			min_jobs = num_jobs;
			rq = entity->rq_list[i];
		}
	}

	return rq;
}