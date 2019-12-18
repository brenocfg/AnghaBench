#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rockchip_drm_private {int /*<<< orphan*/  psr_list_lock; int /*<<< orphan*/  psr_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_crtc; } ;
struct drm_device {int irq_enabled; struct rockchip_drm_private* dev_private; TYPE_1__ mode_config; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int component_bind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  component_unbind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct drm_device*) ; 
 struct rockchip_drm_private* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rockchip_drm_driver ; 
 int /*<<< orphan*/  rockchip_drm_fbdev_fini (struct drm_device*) ; 
 int rockchip_drm_fbdev_init (struct drm_device*) ; 
 int rockchip_drm_init_iommu (struct drm_device*) ; 
 int /*<<< orphan*/  rockchip_drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  rockchip_iommu_cleanup (struct drm_device*) ; 

__attribute__((used)) static int rockchip_drm_bind(struct device *dev)
{
	struct drm_device *drm_dev;
	struct rockchip_drm_private *private;
	int ret;

	drm_dev = drm_dev_alloc(&rockchip_drm_driver, dev);
	if (IS_ERR(drm_dev))
		return PTR_ERR(drm_dev);

	dev_set_drvdata(dev, drm_dev);

	private = devm_kzalloc(drm_dev->dev, sizeof(*private), GFP_KERNEL);
	if (!private) {
		ret = -ENOMEM;
		goto err_free;
	}

	drm_dev->dev_private = private;

	INIT_LIST_HEAD(&private->psr_list);
	mutex_init(&private->psr_list_lock);

	ret = rockchip_drm_init_iommu(drm_dev);
	if (ret)
		goto err_free;

	drm_mode_config_init(drm_dev);

	rockchip_drm_mode_config_init(drm_dev);

	/* Try to bind all sub drivers. */
	ret = component_bind_all(dev, drm_dev);
	if (ret)
		goto err_mode_config_cleanup;

	ret = drm_vblank_init(drm_dev, drm_dev->mode_config.num_crtc);
	if (ret)
		goto err_unbind_all;

	drm_mode_config_reset(drm_dev);

	/*
	 * enable drm irq mode.
	 * - with irq_enabled = true, we can use the vblank feature.
	 */
	drm_dev->irq_enabled = true;

	ret = rockchip_drm_fbdev_init(drm_dev);
	if (ret)
		goto err_unbind_all;

	/* init kms poll for handling hpd */
	drm_kms_helper_poll_init(drm_dev);

	ret = drm_dev_register(drm_dev, 0);
	if (ret)
		goto err_kms_helper_poll_fini;

	return 0;
err_kms_helper_poll_fini:
	drm_kms_helper_poll_fini(drm_dev);
	rockchip_drm_fbdev_fini(drm_dev);
err_unbind_all:
	component_unbind_all(dev, drm_dev);
err_mode_config_cleanup:
	drm_mode_config_cleanup(drm_dev);
	rockchip_iommu_cleanup(drm_dev);
err_free:
	drm_dev->dev_private = NULL;
	dev_set_drvdata(dev, NULL);
	drm_dev_put(drm_dev);
	return ret;
}