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
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  MUTEX_TRYLOCK_FAILED 130 
#define  MUTEX_TRYLOCK_RECURSIVE 129 
#define  MUTEX_TRYLOCK_SUCCESS 128 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int mutex_trylock_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static bool shrinker_lock(struct drm_i915_private *i915, bool *unlock)
{
	switch (mutex_trylock_recursive(&i915->drm.struct_mutex)) {
	case MUTEX_TRYLOCK_RECURSIVE:
		*unlock = false;
		return true;

	case MUTEX_TRYLOCK_FAILED:
		*unlock = false;
		preempt_disable();
		do {
			cpu_relax();
			if (mutex_trylock(&i915->drm.struct_mutex)) {
				*unlock = true;
				break;
			}
		} while (!need_resched());
		preempt_enable();
		return *unlock;

	case MUTEX_TRYLOCK_SUCCESS:
		*unlock = true;
		return true;
	}

	BUG();
}