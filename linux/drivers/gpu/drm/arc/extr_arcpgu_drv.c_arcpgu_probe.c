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
 int /*<<< orphan*/  arcpgu_drm_driver ; 
 int arcpgu_load (struct drm_device*) ; 
 int /*<<< orphan*/  arcpgu_unload (struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int) ; 

__attribute__((used)) static int arcpgu_probe(struct platform_device *pdev)
{
	struct drm_device *drm;
	int ret;

	drm = drm_dev_alloc(&arcpgu_drm_driver, &pdev->dev);
	if (IS_ERR(drm))
		return PTR_ERR(drm);

	ret = arcpgu_load(drm);
	if (ret)
		goto err_unref;

	ret = drm_dev_register(drm, 0);
	if (ret)
		goto err_unload;

	drm_fbdev_generic_setup(drm, 16);

	return 0;

err_unload:
	arcpgu_unload(drm);

err_unref:
	drm_dev_put(drm);

	return ret;
}