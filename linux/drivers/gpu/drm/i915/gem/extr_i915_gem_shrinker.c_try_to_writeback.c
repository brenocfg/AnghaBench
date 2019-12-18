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
struct TYPE_2__ {int madv; } ;
struct drm_i915_gem_object {TYPE_1__ mm; } ;

/* Variables and functions */
#define  I915_MADV_DONTNEED 129 
 unsigned int I915_SHRINK_WRITEBACK ; 
#define  __I915_MADV_PURGED 128 
 int /*<<< orphan*/  i915_gem_object_truncate (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_writeback (struct drm_i915_gem_object*) ; 

__attribute__((used)) static void try_to_writeback(struct drm_i915_gem_object *obj,
			     unsigned int flags)
{
	switch (obj->mm.madv) {
	case I915_MADV_DONTNEED:
		i915_gem_object_truncate(obj);
	case __I915_MADV_PURGED:
		return;
	}

	if (flags & I915_SHRINK_WRITEBACK)
		i915_gem_object_writeback(obj);
}