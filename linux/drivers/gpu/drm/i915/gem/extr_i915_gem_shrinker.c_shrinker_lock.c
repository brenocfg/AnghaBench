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
struct mutex {int dummy; } ;
struct TYPE_2__ {struct mutex struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  I915_MM_SHRINKER ; 
 unsigned int I915_SHRINK_ACTIVE ; 
#define  MUTEX_TRYLOCK_FAILED 130 
#define  MUTEX_TRYLOCK_RECURSIVE 129 
#define  MUTEX_TRYLOCK_SUCCESS 128 
 int /*<<< orphan*/  mutex_lock_killable_nested (struct mutex*,int /*<<< orphan*/ ) ; 
 int mutex_trylock_recursive (struct mutex*) ; 

__attribute__((used)) static bool shrinker_lock(struct drm_i915_private *i915,
			  unsigned int flags,
			  bool *unlock)
{
	struct mutex *m = &i915->drm.struct_mutex;

	switch (mutex_trylock_recursive(m)) {
	case MUTEX_TRYLOCK_RECURSIVE:
		*unlock = false;
		return true;

	case MUTEX_TRYLOCK_FAILED:
		*unlock = false;
		if (flags & I915_SHRINK_ACTIVE &&
		    mutex_lock_killable_nested(m, I915_MM_SHRINKER) == 0)
			*unlock = true;
		return *unlock;

	case MUTEX_TRYLOCK_SUCCESS:
		*unlock = true;
		return true;
	}

	BUG();
}