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
struct drm_gpu_scheduler {int /*<<< orphan*/  job_list_lock; int /*<<< orphan*/  work_tdr; int /*<<< orphan*/  ring_mirror_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  system_wq ; 

void drm_sched_resume_timeout(struct drm_gpu_scheduler *sched,
		unsigned long remaining)
{
	unsigned long flags;

	spin_lock_irqsave(&sched->job_list_lock, flags);

	if (list_empty(&sched->ring_mirror_list))
		cancel_delayed_work(&sched->work_tdr);
	else
		mod_delayed_work(system_wq, &sched->work_tdr, remaining);

	spin_unlock_irqrestore(&sched->job_list_lock, flags);
}