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
struct drm_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int component_bind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  component_unbind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int mcde_modeset_init (struct drm_device*) ; 

__attribute__((used)) static int mcde_drm_bind(struct device *dev)
{
	struct drm_device *drm = dev_get_drvdata(dev);
	int ret;

	drm_mode_config_init(drm);

	ret = component_bind_all(drm->dev, drm);
	if (ret) {
		dev_err(dev, "can't bind component devices\n");
		return ret;
	}

	ret = mcde_modeset_init(drm);
	if (ret)
		goto unbind;

	ret = drm_dev_register(drm, 0);
	if (ret < 0)
		goto unbind;

	return 0;

unbind:
	component_unbind_all(drm->dev, drm);
	return ret;
}