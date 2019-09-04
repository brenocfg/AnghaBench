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
struct i915_gem_active {int /*<<< orphan*/  retire; } ;
typedef  scalar_t__ i915_gem_retire_fn ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_retire_noop ; 
 int /*<<< orphan*/  lockdep_assert_held (struct mutex*) ; 

__attribute__((used)) static inline void
i915_gem_active_set_retire_fn(struct i915_gem_active *active,
			      i915_gem_retire_fn fn,
			      struct mutex *mutex)
{
	lockdep_assert_held(mutex);
	active->retire = fn ?: i915_gem_retire_noop;
}