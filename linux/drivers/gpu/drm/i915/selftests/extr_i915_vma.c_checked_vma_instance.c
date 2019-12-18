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
struct i915_ggtt_view {int dummy; } ;
struct i915_vma {struct i915_ggtt_view const ggtt_view; struct i915_address_space* vm; } ;
struct i915_address_space {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct i915_vma* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_is_ggtt (struct i915_address_space*) ; 
 scalar_t__ i915_vma_compare (struct i915_vma*,struct i915_address_space*,struct i915_ggtt_view const*) ; 
 struct i915_vma* i915_vma_instance (struct drm_i915_gem_object*,struct i915_address_space*,struct i915_ggtt_view const*) ; 
 int /*<<< orphan*/  i915_vma_is_ggtt (struct i915_vma*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static struct i915_vma *
checked_vma_instance(struct drm_i915_gem_object *obj,
		     struct i915_address_space *vm,
		     const struct i915_ggtt_view *view)
{
	struct i915_vma *vma;
	bool ok = true;

	vma = i915_vma_instance(obj, vm, view);
	if (IS_ERR(vma))
		return vma;

	/* Manual checks, will be reinforced by i915_vma_compare! */
	if (vma->vm != vm) {
		pr_err("VMA's vm [%p] does not match request [%p]\n",
		       vma->vm, vm);
		ok = false;
	}

	if (i915_is_ggtt(vm) != i915_vma_is_ggtt(vma)) {
		pr_err("VMA ggtt status [%d] does not match parent [%d]\n",
		       i915_vma_is_ggtt(vma), i915_is_ggtt(vm));
		ok = false;
	}

	if (i915_vma_compare(vma, vm, view)) {
		pr_err("i915_vma_compare failed with create parameters!\n");
		return ERR_PTR(-EINVAL);
	}

	if (i915_vma_compare(vma, vma->vm,
			     i915_vma_is_ggtt(vma) ? &vma->ggtt_view : NULL)) {
		pr_err("i915_vma_compare failed with itself\n");
		return ERR_PTR(-EINVAL);
	}

	if (!ok) {
		pr_err("i915_vma_compare failed to detect the difference!\n");
		return ERR_PTR(-EINVAL);
	}

	return vma;
}