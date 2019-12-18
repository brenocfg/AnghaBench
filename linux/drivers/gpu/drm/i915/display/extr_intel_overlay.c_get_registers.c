#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_overlay {struct i915_vma* reg_bo; struct i915_vma* regs; int /*<<< orphan*/  flip_addr; struct drm_i915_private* i915; } ;
struct TYPE_5__ {TYPE_1__* pages; } ;
struct i915_vma {TYPE_2__ mm; } ;
struct TYPE_6__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_3__ drm; } ;
struct drm_i915_gem_object {TYPE_2__ mm; } ;
struct TYPE_4__ {int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PIN_MAPPABLE ; 
 int PTR_ERR (struct i915_vma*) ; 
 struct i915_vma* i915_gem_object_create_internal (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_gem_object_create_stolen (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_gem_object_ggtt_pin (struct i915_vma*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_ggtt_offset (struct i915_vma*) ; 
 struct i915_vma* i915_vma_pin_iomap (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_registers(struct intel_overlay *overlay, bool use_phys)
{
	struct drm_i915_private *i915 = overlay->i915;
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	int err;

	mutex_lock(&i915->drm.struct_mutex);

	obj = i915_gem_object_create_stolen(i915, PAGE_SIZE);
	if (obj == NULL)
		obj = i915_gem_object_create_internal(i915, PAGE_SIZE);
	if (IS_ERR(obj)) {
		err = PTR_ERR(obj);
		goto err_unlock;
	}

	vma = i915_gem_object_ggtt_pin(obj, NULL, 0, 0, PIN_MAPPABLE);
	if (IS_ERR(vma)) {
		err = PTR_ERR(vma);
		goto err_put_bo;
	}

	if (use_phys)
		overlay->flip_addr = sg_dma_address(obj->mm.pages->sgl);
	else
		overlay->flip_addr = i915_ggtt_offset(vma);
	overlay->regs = i915_vma_pin_iomap(vma);
	i915_vma_unpin(vma);

	if (IS_ERR(overlay->regs)) {
		err = PTR_ERR(overlay->regs);
		goto err_put_bo;
	}

	overlay->reg_bo = obj;
	mutex_unlock(&i915->drm.struct_mutex);
	return 0;

err_put_bo:
	i915_gem_object_put(obj);
err_unlock:
	mutex_unlock(&i915->drm.struct_mutex);
	return err;
}