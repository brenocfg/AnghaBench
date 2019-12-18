#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct evict_vma {TYPE_3__* vma; int /*<<< orphan*/  completion; } ;
struct TYPE_8__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct TYPE_9__ {int /*<<< orphan*/  obj; TYPE_1__* vm; } ;
struct TYPE_7__ {struct drm_i915_private* i915; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_TILING_Y ; 
 int PIN_GLOBAL ; 
 int PIN_MAPPABLE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int i915_gem_object_set_tiling (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int i915_vma_pin (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int i915_vma_pin_fence (TYPE_3__*) ; 
 int /*<<< orphan*/  i915_vma_unpin (TYPE_3__*) ; 
 int /*<<< orphan*/  i915_vma_unpin_fence (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int evict_fence(void *data)
{
	struct evict_vma *arg = data;
	struct drm_i915_private *i915 = arg->vma->vm->i915;
	int err;

	complete(&arg->completion);

	mutex_lock(&i915->drm.struct_mutex);

	/* Mark the fence register as dirty to force the mmio update. */
	err = i915_gem_object_set_tiling(arg->vma->obj, I915_TILING_Y, 512);
	if (err) {
		pr_err("Invalid Y-tiling settings; err:%d\n", err);
		goto out_unlock;
	}

	err = i915_vma_pin(arg->vma, 0, 0, PIN_GLOBAL | PIN_MAPPABLE);
	if (err) {
		pr_err("Unable to pin vma for Y-tiled fence; err:%d\n", err);
		goto out_unlock;
	}

	err = i915_vma_pin_fence(arg->vma);
	i915_vma_unpin(arg->vma);
	if (err) {
		pr_err("Unable to pin Y-tiled fence; err:%d\n", err);
		goto out_unlock;
	}

	i915_vma_unpin_fence(arg->vma);

out_unlock:
	mutex_unlock(&i915->drm.struct_mutex);

	return err;
}