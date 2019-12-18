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
struct i915_ggtt {int /*<<< orphan*/  vm; } ;
struct drm_i915_private {struct i915_ggtt ggtt; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  I915_GTT_PAGE_SIZE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_MAX ; 
 int /*<<< orphan*/  cleanup_objects (struct drm_i915_private*,int /*<<< orphan*/ *) ; 
 int i915_gem_evict_something (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objects ; 
 int populate_ggtt (struct drm_i915_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  unpin_ggtt (struct drm_i915_private*) ; 

__attribute__((used)) static int igt_evict_something(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct i915_ggtt *ggtt = &i915->ggtt;
	LIST_HEAD(objects);
	int err;

	/* Fill the GGTT with pinned objects and try to evict one. */

	err = populate_ggtt(i915, &objects);
	if (err)
		goto cleanup;

	/* Everything is pinned, nothing should happen */
	err = i915_gem_evict_something(&ggtt->vm,
				       I915_GTT_PAGE_SIZE, 0, 0,
				       0, U64_MAX,
				       0);
	if (err != -ENOSPC) {
		pr_err("i915_gem_evict_something failed on a full GGTT with err=%d\n",
		       err);
		goto cleanup;
	}

	unpin_ggtt(i915);

	/* Everything is unpinned, we should be able to evict something */
	err = i915_gem_evict_something(&ggtt->vm,
				       I915_GTT_PAGE_SIZE, 0, 0,
				       0, U64_MAX,
				       0);
	if (err) {
		pr_err("i915_gem_evict_something failed on a full GGTT with err=%d\n",
		       err);
		goto cleanup;
	}

cleanup:
	cleanup_objects(i915, &objects);
	return err;
}