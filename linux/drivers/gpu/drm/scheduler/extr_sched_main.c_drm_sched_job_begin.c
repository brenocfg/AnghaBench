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
struct drm_sched_job {int /*<<< orphan*/  node; struct drm_gpu_scheduler* sched; } ;
struct drm_gpu_scheduler {int /*<<< orphan*/  job_list_lock; int /*<<< orphan*/  ring_mirror_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_sched_start_timeout (struct drm_gpu_scheduler*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void drm_sched_job_begin(struct drm_sched_job *s_job)
{
	struct drm_gpu_scheduler *sched = s_job->sched;
	unsigned long flags;

	spin_lock_irqsave(&sched->job_list_lock, flags);
	list_add_tail(&s_job->node, &sched->ring_mirror_list);
	drm_sched_start_timeout(sched);
	spin_unlock_irqrestore(&sched->job_list_lock, flags);
}