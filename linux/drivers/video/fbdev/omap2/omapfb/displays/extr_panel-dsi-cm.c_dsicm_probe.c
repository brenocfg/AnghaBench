#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {int x_res; int y_res; int pixelclock; } ;
struct TYPE_5__ {int /*<<< orphan*/  dsi_pix_fmt; TYPE_1__ timings; } ;
struct omap_dss_device {int caps; TYPE_2__ panel; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * driver; struct device* dev; } ;
struct panel_drv_data {struct backlight_device* bldev; scalar_t__ use_dsi_backlight; int /*<<< orphan*/  ulps_work; int /*<<< orphan*/  te_timeout_work; int /*<<< orphan*/  ext_te_gpio; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  do_update; int /*<<< orphan*/  lock; TYPE_1__ timings; struct omap_dss_device dssdev; struct platform_device* pdev; } ;
struct backlight_properties {int max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int brightness; void* power; void* fb_blank; } ;
struct backlight_device {TYPE_3__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_RAW ; 
 int ENODEV ; 
 int ENOMEM ; 
 void* FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_IN ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_DSI ; 
 int OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE ; 
 int OMAP_DSS_DISPLAY_CAP_TEAR_ELIM ; 
 int /*<<< orphan*/  OMAP_DSS_DSI_FMT_RGB888 ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct backlight_device* backlight_device_register (int /*<<< orphan*/ ,struct device*,struct panel_drv_data*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  backlight_device_unregister (struct backlight_device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct panel_drv_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  dsicm_attr_group ; 
 int /*<<< orphan*/  dsicm_bl_ops ; 
 int /*<<< orphan*/  dsicm_bl_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  dsicm_hw_reset (struct panel_drv_data*) ; 
 int /*<<< orphan*/  dsicm_ops ; 
 int dsicm_probe_of (struct platform_device*) ; 
 int /*<<< orphan*/  dsicm_te_isr ; 
 int /*<<< orphan*/  dsicm_te_timeout_work_callback ; 
 int /*<<< orphan*/  dsicm_ulps_work ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int omapdss_register_display (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsicm_probe(struct platform_device *pdev)
{
	struct backlight_properties props;
	struct panel_drv_data *ddata;
	struct backlight_device *bldev = NULL;
	struct device *dev = &pdev->dev;
	struct omap_dss_device *dssdev;
	int r;

	dev_dbg(dev, "probe\n");

	if (!pdev->dev.of_node)
		return -ENODEV;

	ddata = devm_kzalloc(dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);
	ddata->pdev = pdev;

	r = dsicm_probe_of(pdev);
	if (r)
		return r;

	ddata->timings.x_res = 864;
	ddata->timings.y_res = 480;
	ddata->timings.pixelclock = 864 * 480 * 60;

	dssdev = &ddata->dssdev;
	dssdev->dev = dev;
	dssdev->driver = &dsicm_ops;
	dssdev->panel.timings = ddata->timings;
	dssdev->type = OMAP_DISPLAY_TYPE_DSI;
	dssdev->owner = THIS_MODULE;

	dssdev->panel.dsi_pix_fmt = OMAP_DSS_DSI_FMT_RGB888;
	dssdev->caps = OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE |
		OMAP_DSS_DISPLAY_CAP_TEAR_ELIM;

	r = omapdss_register_display(dssdev);
	if (r) {
		dev_err(dev, "Failed to register panel\n");
		goto err_reg;
	}

	mutex_init(&ddata->lock);

	atomic_set(&ddata->do_update, 0);

	if (gpio_is_valid(ddata->reset_gpio)) {
		r = devm_gpio_request_one(dev, ddata->reset_gpio,
				GPIOF_OUT_INIT_LOW, "taal rst");
		if (r) {
			dev_err(dev, "failed to request reset gpio\n");
			return r;
		}
	}

	if (gpio_is_valid(ddata->ext_te_gpio)) {
		r = devm_gpio_request_one(dev, ddata->ext_te_gpio,
				GPIOF_IN, "taal irq");
		if (r) {
			dev_err(dev, "GPIO request failed\n");
			return r;
		}

		r = devm_request_irq(dev, gpio_to_irq(ddata->ext_te_gpio),
				dsicm_te_isr,
				IRQF_TRIGGER_RISING,
				"taal vsync", ddata);

		if (r) {
			dev_err(dev, "IRQ request failed\n");
			return r;
		}

		INIT_DEFERRABLE_WORK(&ddata->te_timeout_work,
					dsicm_te_timeout_work_callback);

		dev_dbg(dev, "Using GPIO TE\n");
	}

	INIT_DELAYED_WORK(&ddata->ulps_work, dsicm_ulps_work);

	dsicm_hw_reset(ddata);

	if (ddata->use_dsi_backlight) {
		memset(&props, 0, sizeof(struct backlight_properties));
		props.max_brightness = 255;

		props.type = BACKLIGHT_RAW;
		bldev = backlight_device_register(dev_name(dev),
				dev, ddata, &dsicm_bl_ops, &props);
		if (IS_ERR(bldev)) {
			r = PTR_ERR(bldev);
			goto err_reg;
		}

		ddata->bldev = bldev;

		bldev->props.fb_blank = FB_BLANK_UNBLANK;
		bldev->props.power = FB_BLANK_UNBLANK;
		bldev->props.brightness = 255;

		dsicm_bl_update_status(bldev);
	}

	r = sysfs_create_group(&dev->kobj, &dsicm_attr_group);
	if (r) {
		dev_err(dev, "failed to create sysfs files\n");
		goto err_sysfs_create;
	}

	return 0;

err_sysfs_create:
	if (bldev != NULL)
		backlight_device_unregister(bldev);
err_reg:
	return r;
}