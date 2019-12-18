#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct i915_vma {scalar_t__ fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_vma_unpin_fence (struct i915_vma*) ; 

__attribute__((used)) static inline void
i915_vma_unpin_fence(struct i915_vma *vma)
{
	/* lockdep_assert_held(&vma->vm->i915->drm.struct_mutex); */
	if (vma->fence)
		__i915_vma_unpin_fence(vma);
}