#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i915_vma {TYPE_1__* vm; int /*<<< orphan*/  vm_link; int /*<<< orphan*/  node; scalar_t__ active_count; struct drm_i915_gem_object* obj; } ;
struct i915_request {TYPE_3__* i915; } ;
struct TYPE_8__ {int dirty; int /*<<< orphan*/  link; } ;
struct drm_i915_gem_object {TYPE_4__ mm; scalar_t__ bind_count; int /*<<< orphan*/  resv; scalar_t__ active_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  obj_lock; int /*<<< orphan*/  bound_list; } ;
struct TYPE_7__ {TYPE_2__ mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  inactive_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  drm_mm_node_allocated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_clear_active_reference (struct drm_i915_gem_object*) ; 
 scalar_t__ i915_gem_object_has_active_reference (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_is_active (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_vma_is_active (struct i915_vma*) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_add_excl_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ reservation_object_test_signaled_rcu (int /*<<< orphan*/ ,int) ; 
 scalar_t__ reservation_object_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reservation_object_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__i915_vma_retire(struct i915_vma *vma, struct i915_request *rq)
{
	struct drm_i915_gem_object *obj = vma->obj;

	GEM_BUG_ON(!i915_vma_is_active(vma));
	if (--vma->active_count)
		return;

	GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
	list_move_tail(&vma->vm_link, &vma->vm->inactive_list);

	GEM_BUG_ON(!i915_gem_object_is_active(obj));
	if (--obj->active_count)
		return;

	/* Prune the shared fence arrays iff completely idle (inc. external) */
	if (reservation_object_trylock(obj->resv)) {
		if (reservation_object_test_signaled_rcu(obj->resv, true))
			reservation_object_add_excl_fence(obj->resv, NULL);
		reservation_object_unlock(obj->resv);
	}

	/* Bump our place on the bound list to keep it roughly in LRU order
	 * so that we don't steal from recently used but inactive objects
	 * (unless we are forced to ofc!)
	 */
	spin_lock(&rq->i915->mm.obj_lock);
	if (obj->bind_count)
		list_move_tail(&obj->mm.link, &rq->i915->mm.bound_list);
	spin_unlock(&rq->i915->mm.obj_lock);

	obj->mm.dirty = true; /* be paranoid  */

	if (i915_gem_object_has_active_reference(obj)) {
		i915_gem_object_clear_active_reference(obj);
		i915_gem_object_put(obj);
	}
}