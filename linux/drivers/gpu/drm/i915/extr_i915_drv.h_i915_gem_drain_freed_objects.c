#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  free_work; int /*<<< orphan*/  free_count; } ;
struct drm_i915_private {TYPE_1__ mm; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_barrier () ; 

__attribute__((used)) static inline void i915_gem_drain_freed_objects(struct drm_i915_private *i915)
{
	/*
	 * A single pass should suffice to release all the freed objects (along
	 * most call paths) , but be a little more paranoid in that freeing
	 * the objects does take a little amount of time, during which the rcu
	 * callbacks could have added new objects into the freed list, and
	 * armed the work again.
	 */
	while (atomic_read(&i915->mm.free_count)) {
		flush_work(&i915->mm.free_work);
		rcu_barrier();
	}
}