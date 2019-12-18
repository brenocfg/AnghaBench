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
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct drm_device* nouveau_platform_device_create (struct nvkm_device_tegra_func const*,struct platform_device*,struct nvkm_device**) ; 
 struct nvkm_device_tegra_func* of_device_get_match_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nouveau_platform_probe(struct platform_device *pdev)
{
	const struct nvkm_device_tegra_func *func;
	struct nvkm_device *device = NULL;
	struct drm_device *drm;
	int ret;

	func = of_device_get_match_data(&pdev->dev);

	drm = nouveau_platform_device_create(func, pdev, &device);
	if (IS_ERR(drm))
		return PTR_ERR(drm);

	ret = drm_dev_register(drm, 0);
	if (ret < 0) {
		drm_dev_put(drm);
		return ret;
	}

	return 0;
}