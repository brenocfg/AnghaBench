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
struct drm_gpu_scheduler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_parkme () ; 
 scalar_t__ kthread_should_park () ; 

__attribute__((used)) static bool drm_sched_blocked(struct drm_gpu_scheduler *sched)
{
	if (kthread_should_park()) {
		kthread_parkme();
		return true;
	}

	return false;
}