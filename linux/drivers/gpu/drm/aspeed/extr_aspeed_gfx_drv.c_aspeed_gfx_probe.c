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
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  aspeed_gfx_driver ; 
 int aspeed_gfx_load (struct drm_device*) ; 
 int /*<<< orphan*/  aspeed_gfx_unload (struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aspeed_gfx_probe(struct platform_device *pdev)
{
	struct drm_device *drm;
	int ret;

	drm = drm_dev_alloc(&aspeed_gfx_driver, &pdev->dev);
	if (IS_ERR(drm))
		return PTR_ERR(drm);

	ret = aspeed_gfx_load(drm);
	if (ret)
		goto err_free;

	ret = drm_dev_register(drm, 0);
	if (ret)
		goto err_unload;

	return 0;

err_unload:
	aspeed_gfx_unload(drm);
err_free:
	drm_dev_put(drm);

	return ret;
}