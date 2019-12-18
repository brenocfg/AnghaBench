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
struct drm_gpu_scheduler {int ready; scalar_t__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 

void drm_sched_fini(struct drm_gpu_scheduler *sched)
{
	if (sched->thread)
		kthread_stop(sched->thread);

	sched->ready = false;
}