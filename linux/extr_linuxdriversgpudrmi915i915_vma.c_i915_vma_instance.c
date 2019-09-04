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
struct i915_vma {int dummy; } ;
struct i915_ggtt_view {int dummy; } ;
struct i915_address_space {int closed; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct drm_i915_gem_object {TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_is_ggtt (struct i915_address_space*) ; 
 scalar_t__ i915_vma_compare (struct i915_vma*,struct i915_address_space*,struct i915_ggtt_view const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct i915_vma* vma_create (struct drm_i915_gem_object*,struct i915_address_space*,struct i915_ggtt_view const*) ; 
 struct i915_vma* vma_lookup (struct drm_i915_gem_object*,struct i915_address_space*,struct i915_ggtt_view const*) ; 

struct i915_vma *
i915_vma_instance(struct drm_i915_gem_object *obj,
		  struct i915_address_space *vm,
		  const struct i915_ggtt_view *view)
{
	struct i915_vma *vma;

	lockdep_assert_held(&obj->base.dev->struct_mutex);
	GEM_BUG_ON(view && !i915_is_ggtt(vm));
	GEM_BUG_ON(vm->closed);

	vma = vma_lookup(obj, vm, view);
	if (!vma)
		vma = vma_create(obj, vm, view);

	GEM_BUG_ON(!IS_ERR(vma) && i915_vma_compare(vma, vm, view));
	GEM_BUG_ON(!IS_ERR(vma) && vma_lookup(obj, vm, view) != vma);
	return vma;
}