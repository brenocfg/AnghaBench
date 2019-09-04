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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_gem_wait_for_idle (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies_timeout (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_timeout_killable (int) ; 
 scalar_t__ shrinker_lock (struct drm_i915_private*,int*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static bool
shrinker_lock_uninterruptible(struct drm_i915_private *i915, bool *unlock,
			      int timeout_ms)
{
	unsigned long timeout = jiffies + msecs_to_jiffies_timeout(timeout_ms);

	do {
		if (i915_gem_wait_for_idle(i915,
					   0, MAX_SCHEDULE_TIMEOUT) == 0 &&
		    shrinker_lock(i915, unlock))
			break;

		schedule_timeout_killable(1);
		if (fatal_signal_pending(current))
			return false;

		if (time_after(jiffies, timeout)) {
			pr_err("Unable to lock GPU to purge memory.\n");
			return false;
		}
	} while (1);

	return true;
}