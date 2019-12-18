#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * port; } ;
struct hdlcd_drm_private {TYPE_2__ crtc; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_crtc; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__ mode_config; struct hdlcd_drm_private* dev_private; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int component_bind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  component_unbind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct drm_device*) ; 
 struct hdlcd_drm_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdlcd_driver ; 
 int hdlcd_load (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdlcd_setup_mode_config (struct drm_device*) ; 
 int /*<<< orphan*/ * of_graph_get_port_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_reserved_mem_device_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_set_active (struct device*) ; 

__attribute__((used)) static int hdlcd_drm_bind(struct device *dev)
{
	struct drm_device *drm;
	struct hdlcd_drm_private *hdlcd;
	int ret;

	hdlcd = devm_kzalloc(dev, sizeof(*hdlcd), GFP_KERNEL);
	if (!hdlcd)
		return -ENOMEM;

	drm = drm_dev_alloc(&hdlcd_driver, dev);
	if (IS_ERR(drm))
		return PTR_ERR(drm);

	drm->dev_private = hdlcd;
	dev_set_drvdata(dev, drm);

	hdlcd_setup_mode_config(drm);
	ret = hdlcd_load(drm, 0);
	if (ret)
		goto err_free;

	/* Set the CRTC's port so that the encoder component can find it */
	hdlcd->crtc.port = of_graph_get_port_by_id(dev->of_node, 0);

	ret = component_bind_all(dev, drm);
	if (ret) {
		DRM_ERROR("Failed to bind all components\n");
		goto err_unload;
	}

	ret = pm_runtime_set_active(dev);
	if (ret)
		goto err_pm_active;

	pm_runtime_enable(dev);

	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	if (ret < 0) {
		DRM_ERROR("failed to initialise vblank\n");
		goto err_vblank;
	}

	drm_mode_config_reset(drm);
	drm_kms_helper_poll_init(drm);

	ret = drm_dev_register(drm, 0);
	if (ret)
		goto err_register;

	drm_fbdev_generic_setup(drm, 32);

	return 0;

err_register:
	drm_kms_helper_poll_fini(drm);
err_vblank:
	pm_runtime_disable(drm->dev);
err_pm_active:
	drm_atomic_helper_shutdown(drm);
	component_unbind_all(dev, drm);
err_unload:
	of_node_put(hdlcd->crtc.port);
	hdlcd->crtc.port = NULL;
	drm_irq_uninstall(drm);
	of_reserved_mem_device_release(drm->dev);
err_free:
	drm_mode_config_cleanup(drm);
	dev_set_drvdata(dev, NULL);
	drm_dev_put(drm);

	return ret;
}