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
struct mutex {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_LOCKDEP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_reclaim_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_reclaim_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 

void i915_gem_shrinker_taints_mutex(struct mutex *mutex)
{
	if (!IS_ENABLED(CONFIG_LOCKDEP))
		return;

	fs_reclaim_acquire(GFP_KERNEL);
	mutex_lock(mutex);
	mutex_unlock(mutex);
	fs_reclaim_release(GFP_KERNEL);
}