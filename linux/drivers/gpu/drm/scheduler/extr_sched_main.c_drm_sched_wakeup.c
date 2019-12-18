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
struct drm_gpu_scheduler {int /*<<< orphan*/  wake_up_worker; } ;

/* Variables and functions */
 scalar_t__ drm_sched_ready (struct drm_gpu_scheduler*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void drm_sched_wakeup(struct drm_gpu_scheduler *sched)
{
	if (drm_sched_ready(sched))
		wake_up_interruptible(&sched->wake_up_worker);
}