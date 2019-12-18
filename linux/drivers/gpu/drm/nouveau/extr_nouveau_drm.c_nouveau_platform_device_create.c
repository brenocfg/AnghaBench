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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct nvkm_device_tegra_func {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct drm_device* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  driver_platform ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_config ; 
 int /*<<< orphan*/  nouveau_debug ; 
 int nouveau_drm_device_init (struct drm_device*) ; 
 int /*<<< orphan*/  nvkm_device_del (struct nvkm_device**) ; 
 int nvkm_device_tegra_new (struct nvkm_device_tegra_func const*,struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,unsigned long long,struct nvkm_device**) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct drm_device*) ; 

struct drm_device *
nouveau_platform_device_create(const struct nvkm_device_tegra_func *func,
			       struct platform_device *pdev,
			       struct nvkm_device **pdevice)
{
	struct drm_device *drm;
	int err;

	err = nvkm_device_tegra_new(func, pdev, nouveau_config, nouveau_debug,
				    true, true, ~0ULL, pdevice);
	if (err)
		goto err_free;

	drm = drm_dev_alloc(&driver_platform, &pdev->dev);
	if (IS_ERR(drm)) {
		err = PTR_ERR(drm);
		goto err_free;
	}

	err = nouveau_drm_device_init(drm);
	if (err)
		goto err_put;

	platform_set_drvdata(pdev, drm);

	return drm;

err_put:
	drm_dev_put(drm);
err_free:
	nvkm_device_del(pdevice);

	return ERR_PTR(err);
}