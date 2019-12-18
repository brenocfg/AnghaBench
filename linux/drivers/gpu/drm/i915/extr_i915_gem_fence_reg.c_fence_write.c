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
struct i915_vma {int dummy; } ;
struct i915_fence_reg {int dirty; int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 scalar_t__ IS_GEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i830_write_fence_reg (struct i915_fence_reg*,struct i915_vma*) ; 
 int /*<<< orphan*/  i915_write_fence_reg (struct i915_fence_reg*,struct i915_vma*) ; 
 int /*<<< orphan*/  i965_write_fence_reg (struct i915_fence_reg*,struct i915_vma*) ; 

__attribute__((used)) static void fence_write(struct i915_fence_reg *fence,
			struct i915_vma *vma)
{
	/*
	 * Previous access through the fence register is marshalled by
	 * the mb() inside the fault handlers (i915_gem_release_mmaps)
	 * and explicitly managed for internal users.
	 */

	if (IS_GEN(fence->i915, 2))
		i830_write_fence_reg(fence, vma);
	else if (IS_GEN(fence->i915, 3))
		i915_write_fence_reg(fence, vma);
	else
		i965_write_fence_reg(fence, vma);

	/*
	 * Access through the fenced region afterwards is
	 * ordered by the posting reads whilst writing the registers.
	 */

	fence->dirty = false;
}