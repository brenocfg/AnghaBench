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
struct TYPE_3__ {int /*<<< orphan*/  color; } ;
struct TYPE_4__ {TYPE_1__ head_node; } ;
struct i915_address_space {int /*<<< orphan*/  unbound_list; int /*<<< orphan*/  inactive_list; int /*<<< orphan*/  active_list; int /*<<< orphan*/  free_pages; TYPE_2__ mm; int /*<<< orphan*/  total; int /*<<< orphan*/  mutex; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  I915_COLOR_UNEVICTABLE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_shrinker_taints_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stash_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_address_space_init(struct i915_address_space *vm,
				    struct drm_i915_private *dev_priv)
{
	/*
	 * The vm->mutex must be reclaim safe (for use in the shrinker).
	 * Do a dummy acquire now under fs_reclaim so that any allocation
	 * attempt holding the lock is immediately reported by lockdep.
	 */
	mutex_init(&vm->mutex);
	i915_gem_shrinker_taints_mutex(&vm->mutex);

	GEM_BUG_ON(!vm->total);
	drm_mm_init(&vm->mm, 0, vm->total);
	vm->mm.head_node.color = I915_COLOR_UNEVICTABLE;

	stash_init(&vm->free_pages);

	INIT_LIST_HEAD(&vm->active_list);
	INIT_LIST_HEAD(&vm->inactive_list);
	INIT_LIST_HEAD(&vm->unbound_list);
}