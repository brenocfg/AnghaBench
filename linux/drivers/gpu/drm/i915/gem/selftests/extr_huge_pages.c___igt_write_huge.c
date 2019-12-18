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
typedef  unsigned int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct intel_engine_cs {TYPE_2__* gt; } ;
struct i915_vma {int dummy; } ;
struct i915_gem_context {int /*<<< orphan*/  vm; } ;
struct i915_address_space {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ggtt; } ;
struct TYPE_3__ {struct i915_address_space vm; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 unsigned int PIN_OFFSET_FIXED ; 
 unsigned int PIN_USER ; 
 int PTR_ERR (struct i915_vma*) ; 
 int cpu_check (struct drm_i915_gem_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpu_write (struct i915_vma*,struct i915_gem_context*,struct intel_engine_cs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i915_is_ggtt (struct i915_address_space*) ; 
 int /*<<< orphan*/  i915_vma_destroy (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct drm_i915_gem_object*,struct i915_address_space*,int /*<<< orphan*/ *) ; 
 int i915_vma_pin (struct i915_vma*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int i915_vma_unbind (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int igt_check_page_sizes (struct i915_vma*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static int __igt_write_huge(struct i915_gem_context *ctx,
			    struct intel_engine_cs *engine,
			    struct drm_i915_gem_object *obj,
			    u64 size, u64 offset,
			    u32 dword, u32 val)
{
	struct i915_address_space *vm = ctx->vm ?: &engine->gt->ggtt->vm;
	unsigned int flags = PIN_USER | PIN_OFFSET_FIXED;
	struct i915_vma *vma;
	int err;

	vma = i915_vma_instance(obj, vm, NULL);
	if (IS_ERR(vma))
		return PTR_ERR(vma);

	err = i915_vma_unbind(vma);
	if (err)
		goto out_vma_close;

	err = i915_vma_pin(vma, size, 0, flags | offset);
	if (err) {
		/*
		 * The ggtt may have some pages reserved so
		 * refrain from erroring out.
		 */
		if (err == -ENOSPC && i915_is_ggtt(vm))
			err = 0;

		goto out_vma_close;
	}

	err = igt_check_page_sizes(vma);
	if (err)
		goto out_vma_unpin;

	err = gpu_write(vma, ctx, engine, dword, val);
	if (err) {
		pr_err("gpu-write failed at offset=%llx\n", offset);
		goto out_vma_unpin;
	}

	err = cpu_check(obj, dword, val);
	if (err) {
		pr_err("cpu-check failed at offset=%llx\n", offset);
		goto out_vma_unpin;
	}

out_vma_unpin:
	i915_vma_unpin(vma);
out_vma_close:
	i915_vma_destroy(vma);

	return err;
}