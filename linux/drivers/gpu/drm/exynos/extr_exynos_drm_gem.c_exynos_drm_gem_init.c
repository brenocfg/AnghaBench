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
struct drm_gem_object {int /*<<< orphan*/  filp; } ;
struct exynos_drm_gem {unsigned long size; struct drm_gem_object base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 struct exynos_drm_gem* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int drm_gem_create_mmap_offset (struct drm_gem_object*) ; 
 int drm_gem_object_init (struct drm_device*,struct drm_gem_object*,unsigned long) ; 
 int /*<<< orphan*/  drm_gem_object_release (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct exynos_drm_gem*) ; 
 struct exynos_drm_gem* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct exynos_drm_gem *exynos_drm_gem_init(struct drm_device *dev,
						  unsigned long size)
{
	struct exynos_drm_gem *exynos_gem;
	struct drm_gem_object *obj;
	int ret;

	exynos_gem = kzalloc(sizeof(*exynos_gem), GFP_KERNEL);
	if (!exynos_gem)
		return ERR_PTR(-ENOMEM);

	exynos_gem->size = size;
	obj = &exynos_gem->base;

	ret = drm_gem_object_init(dev, obj, size);
	if (ret < 0) {
		DRM_DEV_ERROR(dev->dev, "failed to initialize gem object\n");
		kfree(exynos_gem);
		return ERR_PTR(ret);
	}

	ret = drm_gem_create_mmap_offset(obj);
	if (ret < 0) {
		drm_gem_object_release(obj);
		kfree(exynos_gem);
		return ERR_PTR(ret);
	}

	DRM_DEV_DEBUG_KMS(dev->dev, "created file object = %pK\n", obj->filp);

	return exynos_gem;
}