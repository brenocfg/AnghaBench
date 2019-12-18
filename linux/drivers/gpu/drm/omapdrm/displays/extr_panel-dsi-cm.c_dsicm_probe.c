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
struct device {int /*<<< orphan*/  kobj; } ;
struct platform_device {struct device dev; } ;
struct omap_dss_device {int display; int caps; int /*<<< orphan*/  ops_flags; int /*<<< orphan*/  of_ports; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * driver; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct TYPE_3__ {int hactive; int vactive; int pixelclock; } ;
struct panel_drv_data {TYPE_2__* extbldev; int /*<<< orphan*/  workqueue; struct backlight_device* bldev; scalar_t__ use_dsi_backlight; int /*<<< orphan*/  ulps_work; int /*<<< orphan*/  te_timeout_work; scalar_t__ ext_te_gpio; int /*<<< orphan*/  do_update; int /*<<< orphan*/  lock; struct omap_dss_device dssdev; TYPE_1__ vm; struct platform_device* pdev; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
struct backlight_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DSI ; 
 int /*<<< orphan*/  OMAP_DSS_DEVICE_OP_MODES ; 
 int OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE ; 
 int OMAP_DSS_DISPLAY_CAP_TEAR_ELIM ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct backlight_device* devm_backlight_device_register (struct device*,int /*<<< orphan*/ ,struct device*,struct panel_drv_data*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 struct panel_drv_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  dsicm_attr_group ; 
 int /*<<< orphan*/  dsicm_bl_ops ; 
 int /*<<< orphan*/  dsicm_dss_driver ; 
 int /*<<< orphan*/  dsicm_hw_reset (struct panel_drv_data*) ; 
 int /*<<< orphan*/  dsicm_ops ; 
 int dsicm_probe_of (struct platform_device*) ; 
 int /*<<< orphan*/  dsicm_te_isr ; 
 int /*<<< orphan*/  dsicm_te_timeout_work_callback ; 
 int /*<<< orphan*/  dsicm_ulps_work ; 
 int /*<<< orphan*/  gpiod_to_irq (scalar_t__) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omapdss_device_register (struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapdss_display_init (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsicm_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct backlight_device *bldev = NULL;
	struct device *dev = &pdev->dev;
	struct omap_dss_device *dssdev;
	int r;

	dev_dbg(dev, "probe\n");

	ddata = devm_kzalloc(dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);
	ddata->pdev = pdev;

	ddata->vm.hactive = 864;
	ddata->vm.vactive = 480;
	ddata->vm.pixelclock = 864 * 480 * 60;

	r = dsicm_probe_of(pdev);
	if (r)
		return r;

	dssdev = &ddata->dssdev;
	dssdev->dev = dev;
	dssdev->ops = &dsicm_ops;
	dssdev->driver = &dsicm_dss_driver;
	dssdev->type = OMAP_DISPLAY_TYPE_DSI;
	dssdev->display = true;
	dssdev->owner = THIS_MODULE;
	dssdev->of_ports = BIT(0);
	dssdev->ops_flags = OMAP_DSS_DEVICE_OP_MODES;

	dssdev->caps = OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE |
		OMAP_DSS_DISPLAY_CAP_TEAR_ELIM;

	omapdss_display_init(dssdev);
	omapdss_device_register(dssdev);

	mutex_init(&ddata->lock);

	atomic_set(&ddata->do_update, 0);

	if (ddata->ext_te_gpio) {
		r = devm_request_irq(dev, gpiod_to_irq(ddata->ext_te_gpio),
				dsicm_te_isr,
				IRQF_TRIGGER_RISING,
				"taal vsync", ddata);

		if (r) {
			dev_err(dev, "IRQ request failed\n");
			goto err_reg;
		}

		INIT_DEFERRABLE_WORK(&ddata->te_timeout_work,
					dsicm_te_timeout_work_callback);

		dev_dbg(dev, "Using GPIO TE\n");
	}

	ddata->workqueue = create_singlethread_workqueue("dsicm_wq");
	if (!ddata->workqueue) {
		r = -ENOMEM;
		goto err_reg;
	}
	INIT_DELAYED_WORK(&ddata->ulps_work, dsicm_ulps_work);

	dsicm_hw_reset(ddata);

	if (ddata->use_dsi_backlight) {
		struct backlight_properties props = { 0 };
		props.max_brightness = 255;
		props.type = BACKLIGHT_RAW;

		bldev = devm_backlight_device_register(dev, dev_name(dev),
			dev, ddata, &dsicm_bl_ops, &props);
		if (IS_ERR(bldev)) {
			r = PTR_ERR(bldev);
			goto err_bl;
		}

		ddata->bldev = bldev;
	}

	r = sysfs_create_group(&dev->kobj, &dsicm_attr_group);
	if (r) {
		dev_err(dev, "failed to create sysfs files\n");
		goto err_bl;
	}

	return 0;

err_bl:
	destroy_workqueue(ddata->workqueue);
err_reg:
	if (ddata->extbldev)
		put_device(&ddata->extbldev->dev);

	return r;
}