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
struct i915_vma {int dummy; } ;
struct i915_ggtt_view {int dummy; } ;
struct i915_address_space {int closed; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_gem_object {TYPE_1__ vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_is_ggtt (struct i915_address_space*) ; 
 scalar_t__ i915_vma_compare (struct i915_vma*,struct i915_address_space*,struct i915_ggtt_view const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct i915_vma* vma_create (struct drm_i915_gem_object*,struct i915_address_space*,struct i915_ggtt_view const*) ; 
 struct i915_vma* vma_lookup (struct drm_i915_gem_object*,struct i915_address_space*,struct i915_ggtt_view const*) ; 

struct i915_vma *
i915_vma_instance(struct drm_i915_gem_object *obj,
		  struct i915_address_space *vm,
		  const struct i915_ggtt_view *view)
{
	struct i915_vma *vma;

	GEM_BUG_ON(view && !i915_is_ggtt(vm));
	GEM_BUG_ON(vm->closed);

	spin_lock(&obj->vma.lock);
	vma = vma_lookup(obj, vm, view);
	spin_unlock(&obj->vma.lock);

	/* vma_create() will resolve the race if another creates the vma */
	if (unlikely(!vma))
		vma = vma_create(obj, vm, view);

	GEM_BUG_ON(!IS_ERR(vma) && i915_vma_compare(vma, vm, view));
	return vma;
}