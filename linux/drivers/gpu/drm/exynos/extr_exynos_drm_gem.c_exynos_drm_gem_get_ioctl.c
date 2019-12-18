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
struct exynos_drm_gem {int /*<<< orphan*/  size; int /*<<< orphan*/  flags; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_exynos_gem_info {int /*<<< orphan*/  size; int /*<<< orphan*/  flags; int /*<<< orphan*/  handle; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct exynos_drm_gem* to_exynos_gem (struct drm_gem_object*) ; 

int exynos_drm_gem_get_ioctl(struct drm_device *dev, void *data,
				      struct drm_file *file_priv)
{
	struct exynos_drm_gem *exynos_gem;
	struct drm_exynos_gem_info *args = data;
	struct drm_gem_object *obj;

	obj = drm_gem_object_lookup(file_priv, args->handle);
	if (!obj) {
		DRM_DEV_ERROR(dev->dev, "failed to lookup gem object.\n");
		return -EINVAL;
	}

	exynos_gem = to_exynos_gem(obj);

	args->flags = exynos_gem->flags;
	args->size = exynos_gem->size;

	drm_gem_object_put_unlocked(obj);

	return 0;
}