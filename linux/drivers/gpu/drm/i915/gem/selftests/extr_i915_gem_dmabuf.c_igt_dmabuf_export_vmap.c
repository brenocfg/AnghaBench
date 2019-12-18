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
struct drm_i915_gem_object {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
struct dma_buf {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  dma_buf_put (struct drm_i915_gem_object*) ; 
 void* dma_buf_vmap (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  dma_buf_vunmap (struct drm_i915_gem_object*,void*) ; 
 struct drm_i915_gem_object* i915_gem_object_create_shmem (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 
 struct drm_i915_gem_object* i915_gem_prime_export (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memchr_inv (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int igt_dmabuf_export_vmap(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct drm_i915_gem_object *obj;
	struct dma_buf *dmabuf;
	void *ptr;
	int err;

	obj = i915_gem_object_create_shmem(i915, PAGE_SIZE);
	if (IS_ERR(obj))
		return PTR_ERR(obj);

	dmabuf = i915_gem_prime_export(&obj->base, 0);
	if (IS_ERR(dmabuf)) {
		pr_err("i915_gem_prime_export failed with err=%d\n",
		       (int)PTR_ERR(dmabuf));
		err = PTR_ERR(dmabuf);
		goto err_obj;
	}
	i915_gem_object_put(obj);

	ptr = dma_buf_vmap(dmabuf);
	if (!ptr) {
		pr_err("dma_buf_vmap failed\n");
		err = -ENOMEM;
		goto out;
	}

	if (memchr_inv(ptr, 0, dmabuf->size)) {
		pr_err("Exported object not initialiased to zero!\n");
		err = -EINVAL;
		goto out;
	}

	memset(ptr, 0xc5, dmabuf->size);

	err = 0;
	dma_buf_vunmap(dmabuf, ptr);
out:
	dma_buf_put(dmabuf);
	return err;

err_obj:
	i915_gem_object_put(obj);
	return err;
}