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
typedef  int u64 ;
struct i915_vma {int dummy; } ;
struct i915_ggtt_view {int dummy; } ;
struct i915_address_space {int dummy; } ;
struct TYPE_4__ {struct i915_address_space vm; } ;
struct drm_i915_private {TYPE_2__ ggtt; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int PIN_GLOBAL ; 
 struct i915_vma* i915_gem_object_pin (struct drm_i915_gem_object*,struct i915_address_space*,struct i915_ggtt_view const*,int,int,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

struct i915_vma *
i915_gem_object_ggtt_pin(struct drm_i915_gem_object *obj,
			 const struct i915_ggtt_view *view,
			 u64 size,
			 u64 alignment,
			 u64 flags)
{
	struct drm_i915_private *dev_priv = to_i915(obj->base.dev);
	struct i915_address_space *vm = &dev_priv->ggtt.vm;

	return i915_gem_object_pin(obj, vm, view, size, alignment,
				   flags | PIN_GLOBAL);
}