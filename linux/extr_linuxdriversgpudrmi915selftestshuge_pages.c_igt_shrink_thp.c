#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ phys; scalar_t__ sg; } ;
struct TYPE_8__ {TYPE_3__ page_sizes; } ;
struct i915_vma {TYPE_4__ mm; } ;
struct i915_gem_context {TYPE_1__* ppgtt; struct drm_i915_private* i915; } ;
struct i915_address_space {int dummy; } ;
struct TYPE_6__ {struct i915_address_space vm; } ;
struct drm_i915_private {int /*<<< orphan*/ * engine; TYPE_2__ ggtt; } ;
struct drm_i915_gem_object {TYPE_4__ mm; } ;
struct TYPE_5__ {struct i915_address_space vm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ I915_GTT_PAGE_SIZE_2M ; 
 scalar_t__ IS_ERR (struct i915_vma*) ; 
 unsigned int PIN_USER ; 
 int PTR_ERR (struct i915_vma*) ; 
 size_t RCS ; 
 int /*<<< orphan*/  SZ_2M ; 
 int cpu_check (struct i915_vma*,int /*<<< orphan*/ ,int) ; 
 int gpu_write (struct i915_vma*,struct i915_gem_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct i915_vma* i915_gem_object_create (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ i915_gem_object_has_pages (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct i915_vma*) ; 
 int /*<<< orphan*/  i915_gem_shrink_all (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_vma_close (struct i915_vma*) ; 
 struct i915_vma* i915_vma_instance (struct i915_vma*,struct i915_address_space*,int /*<<< orphan*/ *) ; 
 int i915_vma_pin (struct i915_vma*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  i915_vma_unpin (struct i915_vma*) ; 
 int /*<<< orphan*/  igt_can_allocate_thp (struct drm_i915_private*) ; 
 int igt_check_page_sizes (struct i915_vma*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int igt_shrink_thp(void *arg)
{
	struct i915_gem_context *ctx = arg;
	struct drm_i915_private *i915 = ctx->i915;
	struct i915_address_space *vm =
		ctx->ppgtt ? &ctx->ppgtt->vm : &i915->ggtt.vm;
	struct drm_i915_gem_object *obj;
	struct i915_vma *vma;
	unsigned int flags = PIN_USER;
	int err;

	/*
	 * Sanity check shrinking huge-paged object -- make sure nothing blows
	 * up.
	 */

	if (!igt_can_allocate_thp(i915)) {
		pr_info("missing THP support, skipping\n");
		return 0;
	}

	obj = i915_gem_object_create(i915, SZ_2M);
	if (IS_ERR(obj))
		return PTR_ERR(obj);

	vma = i915_vma_instance(obj, vm, NULL);
	if (IS_ERR(vma)) {
		err = PTR_ERR(vma);
		goto out_put;
	}

	err = i915_vma_pin(vma, 0, 0, flags);
	if (err)
		goto out_close;

	if (obj->mm.page_sizes.phys < I915_GTT_PAGE_SIZE_2M) {
		pr_info("failed to allocate THP, finishing test early\n");
		goto out_unpin;
	}

	err = igt_check_page_sizes(vma);
	if (err)
		goto out_unpin;

	err = gpu_write(vma, ctx, i915->engine[RCS], 0, 0xdeadbeaf);
	if (err)
		goto out_unpin;

	i915_vma_unpin(vma);

	/*
	 * Now that the pages are *unpinned* shrink-all should invoke
	 * shmem to truncate our pages.
	 */
	i915_gem_shrink_all(i915);
	if (i915_gem_object_has_pages(obj)) {
		pr_err("shrink-all didn't truncate the pages\n");
		err = -EINVAL;
		goto out_close;
	}

	if (obj->mm.page_sizes.sg || obj->mm.page_sizes.phys) {
		pr_err("residual page-size bits left\n");
		err = -EINVAL;
		goto out_close;
	}

	err = i915_vma_pin(vma, 0, 0, flags);
	if (err)
		goto out_close;

	err = cpu_check(obj, 0, 0xdeadbeaf);

out_unpin:
	i915_vma_unpin(vma);
out_close:
	i915_vma_close(vma);
out_put:
	i915_gem_object_put(obj);

	return err;
}