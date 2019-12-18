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
struct drm_i915_private {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  drain_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  rcu_barrier () ; 

__attribute__((used)) static inline void i915_gem_drain_workqueue(struct drm_i915_private *i915)
{
	/*
	 * Similar to objects above (see i915_gem_drain_freed-objects), in
	 * general we have workers that are armed by RCU and then rearm
	 * themselves in their callbacks. To be paranoid, we need to
	 * drain the workqueue a second time after waiting for the RCU
	 * grace period so that we catch work queued via RCU from the first
	 * pass. As neither drain_workqueue() nor flush_workqueue() report
	 * a result, we make an assumption that we only don't require more
	 * than 3 passes to catch all _recursive_ RCU delayed work.
	 *
	 */
	int pass = 3;
	do {
		flush_workqueue(i915->wq);
		rcu_barrier();
		i915_gem_drain_freed_objects(i915);
	} while (--pass);
	drain_workqueue(i915->wq);
}