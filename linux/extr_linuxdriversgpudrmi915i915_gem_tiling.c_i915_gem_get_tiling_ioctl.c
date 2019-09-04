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
struct TYPE_2__ {scalar_t__ bit_6_swizzle_x; scalar_t__ bit_6_swizzle_y; } ;
struct drm_i915_private {int quirks; TYPE_1__ mm; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  tiling_and_stride; } ;
struct drm_i915_gem_get_tiling {int tiling_mode; scalar_t__ swizzle_mode; scalar_t__ phys_swizzle_mode; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ I915_BIT_6_SWIZZLE_9 ; 
 scalar_t__ I915_BIT_6_SWIZZLE_9_10 ; 
 scalar_t__ I915_BIT_6_SWIZZLE_9_10_17 ; 
 scalar_t__ I915_BIT_6_SWIZZLE_9_17 ; 
 scalar_t__ I915_BIT_6_SWIZZLE_NONE ; 
 scalar_t__ I915_BIT_6_SWIZZLE_UNKNOWN ; 
#define  I915_TILING_NONE 130 
#define  I915_TILING_X 129 
#define  I915_TILING_Y 128 
 int QUIRK_PIN_SWIZZLED_PAGES ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int TILING_MASK ; 
 struct drm_i915_gem_object* i915_gem_object_lookup_rcu (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 scalar_t__ unlikely (int) ; 

int
i915_gem_get_tiling_ioctl(struct drm_device *dev, void *data,
			  struct drm_file *file)
{
	struct drm_i915_gem_get_tiling *args = data;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_i915_gem_object *obj;
	int err = -ENOENT;

	rcu_read_lock();
	obj = i915_gem_object_lookup_rcu(file, args->handle);
	if (obj) {
		args->tiling_mode =
			READ_ONCE(obj->tiling_and_stride) & TILING_MASK;
		err = 0;
	}
	rcu_read_unlock();
	if (unlikely(err))
		return err;

	switch (args->tiling_mode) {
	case I915_TILING_X:
		args->swizzle_mode = dev_priv->mm.bit_6_swizzle_x;
		break;
	case I915_TILING_Y:
		args->swizzle_mode = dev_priv->mm.bit_6_swizzle_y;
		break;
	default:
	case I915_TILING_NONE:
		args->swizzle_mode = I915_BIT_6_SWIZZLE_NONE;
		break;
	}

	/* Hide bit 17 from the user -- see comment in i915_gem_set_tiling */
	if (dev_priv->quirks & QUIRK_PIN_SWIZZLED_PAGES)
		args->phys_swizzle_mode = I915_BIT_6_SWIZZLE_UNKNOWN;
	else
		args->phys_swizzle_mode = args->swizzle_mode;
	if (args->swizzle_mode == I915_BIT_6_SWIZZLE_9_17)
		args->swizzle_mode = I915_BIT_6_SWIZZLE_9;
	if (args->swizzle_mode == I915_BIT_6_SWIZZLE_9_10_17)
		args->swizzle_mode = I915_BIT_6_SWIZZLE_9_10;

	return 0;
}