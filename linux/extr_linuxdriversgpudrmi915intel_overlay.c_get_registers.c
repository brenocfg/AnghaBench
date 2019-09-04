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
struct intel_overlay {struct i915_vma* reg_bo; struct i915_vma* regs; int /*<<< orphan*/  flip_addr; int /*<<< orphan*/  i915; } ;
struct TYPE_4__ {TYPE_1__* pages; } ;
struct i915_vma {TYPE_2__ mm; } ;
struct drm_i915_gem_object {TYPE_2__ mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PIN_MAPPABLE ; 
 int PTR_ERR (struct i915_vma*) ; 
 struct i915_vma* i915_gem_object_create_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_gem_object_create_stolen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i915_vma* i915_gem_object_ggtt_pin (struct i915_vma*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_ggtt_offset (struct i915_vma*) ; 
 struct i915_vma* i915_vma_pin_iomap (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_registers(struct intel_overlay *overlay, bool use_phys)
{
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	int err;

	obj = i915_gem_object_create_stolen(overlay->i915, PAGE_SIZE);
	if (obj == NULL)
		obj = i915_gem_object_create_internal(overlay->i915, PAGE_SIZE);
	if (IS_ERR(obj))
		return PTR_ERR(obj);

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
	return 0;

err_put_bo:
	i915_gem_object_put(obj);
	return err;
}