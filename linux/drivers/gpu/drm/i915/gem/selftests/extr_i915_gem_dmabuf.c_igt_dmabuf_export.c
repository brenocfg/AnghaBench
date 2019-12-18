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
struct drm_i915_private {int dummy; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  base; } ;
struct dma_buf {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  dma_buf_put (struct drm_i915_gem_object*) ; 
 struct drm_i915_gem_object* i915_gem_object_create_shmem (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 struct drm_i915_gem_object* i915_gem_prime_export (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int igt_dmabuf_export(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct drm_i915_gem_object *obj;
	struct dma_buf *dmabuf;

	obj = i915_gem_object_create_shmem(i915, PAGE_SIZE);
	if (IS_ERR(obj))
		return PTR_ERR(obj);

	dmabuf = i915_gem_prime_export(&obj->base, 0);
	i915_gem_object_put(obj);
	if (IS_ERR(dmabuf)) {
		pr_err("i915_gem_prime_export failed with err=%d\n",
		       (int)PTR_ERR(dmabuf));
		return PTR_ERR(dmabuf);
	}

	dma_buf_put(dmabuf);
	return 0;
}