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
typedef  int u32 ;
struct intel_engine_cs {int dummy; } ;
struct i915_vma {int size; int /*<<< orphan*/  obj; } ;
struct i915_gem_context {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  i915_gem_object_lock (int /*<<< orphan*/ ) ; 
 int i915_gem_object_set_to_gtt_domain (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i915_gem_object_unlock (int /*<<< orphan*/ ) ; 
 int igt_gpu_fill_dw (struct i915_vma*,struct i915_gem_context*,struct intel_engine_cs*,int,int,int) ; 

__attribute__((used)) static int gpu_write(struct i915_vma *vma,
		     struct i915_gem_context *ctx,
		     struct intel_engine_cs *engine,
		     u32 dw,
		     u32 val)
{
	int err;

	i915_gem_object_lock(vma->obj);
	err = i915_gem_object_set_to_gtt_domain(vma->obj, true);
	i915_gem_object_unlock(vma->obj);
	if (err)
		return err;

	return igt_gpu_fill_dw(vma, ctx, engine, dw * sizeof(u32),
			       vma->size >> PAGE_SHIFT, val);
}