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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct intel_guc {int dummy; } ;
struct intel_gt {TYPE_1__* ggtt; int /*<<< orphan*/  i915; } ;
struct i915_vma {int dummy; } ;
typedef  struct i915_vma drm_i915_gem_object ;
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 struct i915_vma* ERR_CAST (struct i915_vma*) ; 
 struct i915_vma* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int PIN_GLOBAL ; 
 int PIN_OFFSET_BIAS ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 struct i915_vma* i915_gem_object_create_shmem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct i915_vma*) ; 
 int i915_ggtt_pin_bias (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct i915_vma*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct i915_vma* i915_vma_make_unshrinkable (struct i915_vma*) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct i915_vma *intel_guc_allocate_vma(struct intel_guc *guc, u32 size)
{
	struct intel_gt *gt = guc_to_gt(guc);
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	u64 flags;
	int ret;

	obj = i915_gem_object_create_shmem(gt->i915, size);
	if (IS_ERR(obj))
		return ERR_CAST(obj);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, NULL);
	if (IS_ERR(vma))
		goto err;

	flags = PIN_GLOBAL | PIN_OFFSET_BIAS | i915_ggtt_pin_bias(vma);
	ret = i915_vma_pin(vma, 0, 0, flags);
	if (ret) {
		vma = ERR_PTR(ret);
		goto err;
	}

	return i915_vma_make_unshrinkable(vma);

err:
	i915_gem_object_put(obj);
	return vma;
}