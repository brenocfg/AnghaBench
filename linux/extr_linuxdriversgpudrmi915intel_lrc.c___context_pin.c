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
struct i915_vma {int flags; int /*<<< orphan*/  obj; } ;
struct i915_gem_context {int ggtt_offset_bias; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_LR_CONTEXT_ALIGN ; 
 int I915_VMA_GLOBAL_BIND ; 
 unsigned int PIN_GLOBAL ; 
 unsigned int PIN_HIGH ; 
 unsigned int PIN_OFFSET_BIAS ; 
 int i915_gem_object_set_to_gtt_domain (int /*<<< orphan*/ ,int) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int __context_pin(struct i915_gem_context *ctx, struct i915_vma *vma)
{
	unsigned int flags;
	int err;

	/*
	 * Clear this page out of any CPU caches for coherent swap-in/out.
	 * We only want to do this on the first bind so that we do not stall
	 * on an active context (which by nature is already on the GPU).
	 */
	if (!(vma->flags & I915_VMA_GLOBAL_BIND)) {
		err = i915_gem_object_set_to_gtt_domain(vma->obj, true);
		if (err)
			return err;
	}

	flags = PIN_GLOBAL | PIN_HIGH;
	if (ctx->ggtt_offset_bias)
		flags |= PIN_OFFSET_BIAS | ctx->ggtt_offset_bias;

	return i915_vma_pin(vma, 0, GEN8_LR_CONTEXT_ALIGN, flags);
}