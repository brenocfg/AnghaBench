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
struct intel_gt {TYPE_1__* ggtt; struct drm_i915_private* i915; } ;
struct i915_vma {int dummy; } ;
struct drm_i915_private {int dummy; } ;
typedef  struct i915_vma drm_i915_gem_object ;
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 struct i915_vma* ERR_CAST (struct i915_vma*) ; 
 int /*<<< orphan*/  I915_CACHE_LLC ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct i915_vma* i915_gem_object_create_internal (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_gem_object_set_cache_coherency (struct i915_vma*,int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_vma_instance (struct i915_vma*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct i915_vma *__hwsp_alloc(struct intel_gt *gt)
{
	struct drm_i915_private *i915 = gt->i915;
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;

	obj = i915_gem_object_create_internal(i915, PAGE_SIZE);
	if (IS_ERR(obj))
		return ERR_CAST(obj);

	i915_gem_object_set_cache_coherency(obj, I915_CACHE_LLC);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, NULL);
	if (IS_ERR(vma))
		i915_gem_object_put(obj);

	return vma;
}