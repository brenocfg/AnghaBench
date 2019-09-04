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
struct exynos_drm_gem {int /*<<< orphan*/  base; } ;
struct drm_file {int dummy; } ;
struct drm_exynos_gem_create {int /*<<< orphan*/  handle; int /*<<< orphan*/  size; int /*<<< orphan*/  flags; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct exynos_drm_gem*) ; 
 int PTR_ERR (struct exynos_drm_gem*) ; 
 struct exynos_drm_gem* exynos_drm_gem_create (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_drm_gem_destroy (struct exynos_drm_gem*) ; 
 int exynos_drm_gem_handle_create (int /*<<< orphan*/ *,struct drm_file*,int /*<<< orphan*/ *) ; 

int exynos_drm_gem_create_ioctl(struct drm_device *dev, void *data,
				struct drm_file *file_priv)
{
	struct drm_exynos_gem_create *args = data;
	struct exynos_drm_gem *exynos_gem;
	int ret;

	exynos_gem = exynos_drm_gem_create(dev, args->flags, args->size);
	if (IS_ERR(exynos_gem))
		return PTR_ERR(exynos_gem);

	ret = exynos_drm_gem_handle_create(&exynos_gem->base, file_priv,
					   &args->handle);
	if (ret) {
		exynos_drm_gem_destroy(exynos_gem);
		return ret;
	}

	return 0;
}