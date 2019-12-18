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
typedef  int /*<<< orphan*/  u64 ;
struct i915_vma {struct i915_address_space* vm; } ;
struct i915_execbuffer {struct i915_vma** vma; struct drm_i915_private* i915; } ;
struct i915_address_space {scalar_t__ has_read_only; } ;
struct TYPE_2__ {struct i915_address_space vm; } ;
struct drm_i915_private {TYPE_1__ ggtt; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 scalar_t__ CMDPARSER_USES_GGTT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  EINVAL ; 
 struct i915_vma* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIN_GLOBAL ; 
 int /*<<< orphan*/  PIN_USER ; 
 struct i915_vma* i915_gem_object_pin (struct drm_i915_gem_object*,struct i915_address_space*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_set_readonly (struct drm_i915_gem_object*) ; 

__attribute__((used)) static struct i915_vma *
shadow_batch_pin(struct i915_execbuffer *eb, struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *dev_priv = eb->i915;
	struct i915_vma * const vma = *eb->vma;
	struct i915_address_space *vm;
	u64 flags;

	/*
	 * PPGTT backed shadow buffers must be mapped RO, to prevent
	 * post-scan tampering
	 */
	if (CMDPARSER_USES_GGTT(dev_priv)) {
		flags = PIN_GLOBAL;
		vm = &dev_priv->ggtt.vm;
	} else if (vma->vm->has_read_only) {
		flags = PIN_USER;
		vm = vma->vm;
		i915_gem_object_set_readonly(obj);
	} else {
		DRM_DEBUG("Cannot prevent post-scan tampering without RO capable vm\n");
		return ERR_PTR(-EINVAL);
	}

	return i915_gem_object_pin(obj, vm, NULL, 0, 0, flags);
}