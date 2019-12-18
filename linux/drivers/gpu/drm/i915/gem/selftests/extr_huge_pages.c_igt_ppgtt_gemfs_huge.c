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
struct i915_gem_context {struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {scalar_t__ phys; } ;
struct TYPE_4__ {TYPE_1__ page_sizes; } ;
struct drm_i915_gem_object {TYPE_2__ mm; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int const*) ; 
 scalar_t__ I915_GTT_PAGE_SIZE_2M ; 
 int /*<<< orphan*/  I915_MM_NORMAL ; 
 scalar_t__ IS_ERR (struct drm_i915_gem_object*) ; 
 int PTR_ERR (struct drm_i915_gem_object*) ; 
#define  SZ_16M 132 
#define  SZ_2M 131 
#define  SZ_32M 130 
#define  SZ_4M 129 
#define  SZ_8M 128 
 int /*<<< orphan*/  __i915_gem_object_put_pages (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 struct drm_i915_gem_object* i915_gem_object_create_shmem (struct drm_i915_private*,unsigned int) ; 
 int i915_gem_object_pin_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_unpin_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  igt_can_allocate_thp (struct drm_i915_private*) ; 
 int igt_write_huge (struct i915_gem_context*,struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int igt_ppgtt_gemfs_huge(void *arg)
{
	struct i915_gem_context *ctx = arg;
	struct drm_i915_private *i915 = ctx->i915;
	struct drm_i915_gem_object *obj;
	static const unsigned int sizes[] = {
		SZ_2M,
		SZ_4M,
		SZ_8M,
		SZ_16M,
		SZ_32M,
	};
	int i;
	int err;

	/*
	 * Sanity check that the HW uses huge pages correctly through gemfs --
	 * ensure that our writes land in the right place.
	 */

	if (!igt_can_allocate_thp(i915)) {
		pr_info("missing THP support, skipping\n");
		return 0;
	}

	for (i = 0; i < ARRAY_SIZE(sizes); ++i) {
		unsigned int size = sizes[i];

		obj = i915_gem_object_create_shmem(i915, size);
		if (IS_ERR(obj))
			return PTR_ERR(obj);

		err = i915_gem_object_pin_pages(obj);
		if (err)
			goto out_put;

		if (obj->mm.page_sizes.phys < I915_GTT_PAGE_SIZE_2M) {
			pr_info("finishing test early, gemfs unable to allocate huge-page(s) with size=%u\n",
				size);
			goto out_unpin;
		}

		err = igt_write_huge(ctx, obj);
		if (err) {
			pr_err("gemfs write-huge failed with size=%u\n",
			       size);
			goto out_unpin;
		}

		i915_gem_object_unpin_pages(obj);
		__i915_gem_object_put_pages(obj, I915_MM_NORMAL);
		i915_gem_object_put(obj);
	}

	return 0;

out_unpin:
	i915_gem_object_unpin_pages(obj);
out_put:
	i915_gem_object_put(obj);

	return err;
}