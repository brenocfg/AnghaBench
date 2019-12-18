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
struct i915_vma {int dummy; } ;
struct i915_address_space {scalar_t__ has_read_only; struct drm_i915_private* i915; } ;
struct i915_ggtt {struct i915_address_space vm; } ;
struct drm_i915_private {int dummy; } ;
typedef  struct i915_vma drm_i915_gem_object ;

/* Variables and functions */
 struct i915_vma* ERR_CAST (struct i915_vma*) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 struct i915_vma* i915_gem_object_create_internal (struct drm_i915_private*,int) ; 
 struct i915_vma* i915_gem_object_create_stolen (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_gem_object_set_readonly (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct i915_vma*,struct i915_address_space*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct i915_vma *create_ring_vma(struct i915_ggtt *ggtt, int size)
{
	struct i915_address_space *vm = &ggtt->vm;
	struct drm_i915_private *i915 = vm->i915;
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;

	obj = i915_gem_object_create_stolen(i915, size);
	if (!obj)
		obj = i915_gem_object_create_internal(i915, size);
	if (IS_ERR(obj))
		return ERR_CAST(obj);

	/*
	 * Mark ring buffers as read-only from GPU side (so no stray overwrites)
	 * if supported by the platform's GGTT.
	 */
	if (vm->has_read_only)
		i915_gem_object_set_readonly(obj);

	vma = i915_vma_instance(obj, vm, NULL);
	if (IS_ERR(vma))
		goto err;

	return vma;

err:
	i915_gem_object_put(obj);
	return vma;
}