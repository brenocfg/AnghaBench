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
struct drm_gem_object {scalar_t__ import_attach; int /*<<< orphan*/  handle_count; int /*<<< orphan*/  dev; } ;
struct exynos_drm_gem {int /*<<< orphan*/  sgt; struct drm_gem_object base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (struct drm_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_drm_free_buf (struct exynos_drm_gem*) ; 
 int /*<<< orphan*/  kfree (struct exynos_drm_gem*) ; 
 int /*<<< orphan*/  to_dma_dev (int /*<<< orphan*/ ) ; 

void exynos_drm_gem_destroy(struct exynos_drm_gem *exynos_gem)
{
	struct drm_gem_object *obj = &exynos_gem->base;

	DRM_DEV_DEBUG_KMS(to_dma_dev(obj->dev), "handle count = %d\n",
			  obj->handle_count);

	/*
	 * do not release memory region from exporter.
	 *
	 * the region will be released by exporter
	 * once dmabuf's refcount becomes 0.
	 */
	if (obj->import_attach)
		drm_prime_gem_destroy(obj, exynos_gem->sgt);
	else
		exynos_drm_free_buf(exynos_gem);

	/* release file pointer to gem object. */
	drm_gem_object_release(obj);

	kfree(exynos_gem);
}