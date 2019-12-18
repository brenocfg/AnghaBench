#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mutex {int /*<<< orphan*/  dep_map; } ;
struct TYPE_4__ {int /*<<< orphan*/  dep_map; } ;
struct TYPE_3__ {TYPE_2__ struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_LOCKDEP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_MM_NORMAL ; 
 int /*<<< orphan*/  I915_MM_SHRINKER ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  fs_reclaim_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_reclaim_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held_type (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i915_gem_shrinker_taints_mutex(struct drm_i915_private *i915,
				    struct mutex *mutex)
{
	bool unlock = false;

	if (!IS_ENABLED(CONFIG_LOCKDEP))
		return;

	if (!lockdep_is_held_type(&i915->drm.struct_mutex, -1)) {
		mutex_acquire(&i915->drm.struct_mutex.dep_map,
			      I915_MM_NORMAL, 0, _RET_IP_);
		unlock = true;
	}

	fs_reclaim_acquire(GFP_KERNEL);

	/*
	 * As we invariably rely on the struct_mutex within the shrinker,
	 * but have a complicated recursion dance, taint all the mutexes used
	 * within the shrinker with the struct_mutex. For completeness, we
	 * taint with all subclass of struct_mutex, even though we should
	 * only need tainting by I915_MM_NORMAL to catch possible ABBA
	 * deadlocks from using struct_mutex inside @mutex.
	 */
	mutex_acquire(&i915->drm.struct_mutex.dep_map,
		      I915_MM_SHRINKER, 0, _RET_IP_);

	mutex_acquire(&mutex->dep_map, 0, 0, _RET_IP_);
	mutex_release(&mutex->dep_map, 0, _RET_IP_);

	mutex_release(&i915->drm.struct_mutex.dep_map, 0, _RET_IP_);

	fs_reclaim_release(GFP_KERNEL);

	if (unlock)
		mutex_release(&i915->drm.struct_mutex.dep_map, 0, _RET_IP_);
}