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
typedef  int /*<<< orphan*/  u32 ;
struct intel_guc {int ggtt_pin_bias; } ;
struct i915_vma {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;
struct drm_i915_private {TYPE_1__ ggtt; } ;
typedef  struct i915_vma drm_i915_gem_object ;

/* Variables and functions */
 struct i915_vma* ERR_CAST (struct i915_vma*) ; 
 struct i915_vma* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PIN_GLOBAL ; 
 int PIN_OFFSET_BIAS ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 struct i915_vma* i915_gem_object_create (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct i915_vma*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct i915_vma *intel_guc_allocate_vma(struct intel_guc *guc, u32 size)
{
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	int ret;

	obj = i915_gem_object_create(dev_priv, size);
	if (IS_ERR(obj))
		return ERR_CAST(obj);

	vma = i915_vma_instance(obj, &dev_priv->ggtt.vm, NULL);
	if (IS_ERR(vma))
		goto err;

	ret = i915_vma_pin(vma, 0, PAGE_SIZE,
			   PIN_GLOBAL | PIN_OFFSET_BIAS | guc->ggtt_pin_bias);
	if (ret) {
		vma = ERR_PTR(ret);
		goto err;
	}

	return vma;

err:
	i915_gem_object_put(obj);
	return vma;
}