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
struct soc_device_attribute {scalar_t__ data; } ;
struct omap_drm_private {unsigned int omaprev; unsigned int num_pipes; int /*<<< orphan*/  wq; TYPE_1__* pipes; struct device* dev; int /*<<< orphan*/  dispc; TYPE_2__* dispc_ops; int /*<<< orphan*/  max_bandwidth; int /*<<< orphan*/  obj_list; int /*<<< orphan*/  list_lock; int /*<<< orphan*/  dss; struct drm_device* ddev; } ;
struct drm_device {struct omap_drm_private* dev_private; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_memory_bandwidth_limit ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dispc_get_dispc (int /*<<< orphan*/ ) ; 
 TYPE_2__* dispc_get_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (int /*<<< orphan*/ ) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_crtc_pre_init (struct omap_drm_private*) ; 
 int /*<<< orphan*/  omap_crtc_pre_uninit (struct omap_drm_private*) ; 
 int /*<<< orphan*/  omap_disconnect_pipelines (struct drm_device*) ; 
 int /*<<< orphan*/  omap_drm_driver ; 
 int /*<<< orphan*/  omap_drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  omap_fbdev_fini (struct drm_device*) ; 
 int /*<<< orphan*/  omap_fbdev_init (struct drm_device*) ; 
 int /*<<< orphan*/  omap_gem_deinit (struct drm_device*) ; 
 int /*<<< orphan*/  omap_gem_init (struct drm_device*) ; 
 int /*<<< orphan*/  omap_modeset_disable_external_hpd (struct drm_device*) ; 
 int /*<<< orphan*/  omap_modeset_enable_external_hpd (struct drm_device*) ; 
 int omap_modeset_init (struct drm_device*) ; 
 int /*<<< orphan*/  omapdrm_soc_devices ; 
 int /*<<< orphan*/  omapdss_get_dss () ; 
 struct soc_device_attribute* soc_device_match (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omapdrm_init(struct omap_drm_private *priv, struct device *dev)
{
	const struct soc_device_attribute *soc;
	struct drm_device *ddev;
	unsigned int i;
	int ret;

	DBG("%s", dev_name(dev));

	/* Allocate and initialize the DRM device. */
	ddev = drm_dev_alloc(&omap_drm_driver, dev);
	if (IS_ERR(ddev))
		return PTR_ERR(ddev);

	priv->ddev = ddev;
	ddev->dev_private = priv;

	priv->dev = dev;
	priv->dss = omapdss_get_dss();
	priv->dispc = dispc_get_dispc(priv->dss);
	priv->dispc_ops = dispc_get_ops(priv->dss);

	omap_crtc_pre_init(priv);

	soc = soc_device_match(omapdrm_soc_devices);
	priv->omaprev = soc ? (unsigned int)soc->data : 0;
	priv->wq = alloc_ordered_workqueue("omapdrm", 0);

	mutex_init(&priv->list_lock);
	INIT_LIST_HEAD(&priv->obj_list);

	/* Get memory bandwidth limits */
	if (priv->dispc_ops->get_memory_bandwidth_limit)
		priv->max_bandwidth =
			priv->dispc_ops->get_memory_bandwidth_limit(priv->dispc);

	omap_gem_init(ddev);

	ret = omap_modeset_init(ddev);
	if (ret) {
		dev_err(priv->dev, "omap_modeset_init failed: ret=%d\n", ret);
		goto err_gem_deinit;
	}

	/* Initialize vblank handling, start with all CRTCs disabled. */
	ret = drm_vblank_init(ddev, priv->num_pipes);
	if (ret) {
		dev_err(priv->dev, "could not init vblank\n");
		goto err_cleanup_modeset;
	}

	for (i = 0; i < priv->num_pipes; i++)
		drm_crtc_vblank_off(priv->pipes[i].crtc);

	omap_fbdev_init(ddev);

	drm_kms_helper_poll_init(ddev);
	omap_modeset_enable_external_hpd(ddev);

	/*
	 * Register the DRM device with the core and the connectors with
	 * sysfs.
	 */
	ret = drm_dev_register(ddev, 0);
	if (ret)
		goto err_cleanup_helpers;

	return 0;

err_cleanup_helpers:
	omap_modeset_disable_external_hpd(ddev);
	drm_kms_helper_poll_fini(ddev);

	omap_fbdev_fini(ddev);
err_cleanup_modeset:
	drm_mode_config_cleanup(ddev);
	omap_drm_irq_uninstall(ddev);
err_gem_deinit:
	omap_gem_deinit(ddev);
	destroy_workqueue(priv->wq);
	omap_disconnect_pipelines(ddev);
	omap_crtc_pre_uninit(priv);
	drm_dev_put(ddev);
	return ret;
}