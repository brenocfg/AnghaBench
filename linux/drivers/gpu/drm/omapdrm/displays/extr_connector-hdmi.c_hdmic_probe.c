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
struct omap_dss_device {int display; int ops_flags; int /*<<< orphan*/  of_ports; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; } ;
struct panel_drv_data {struct gpio_desc* hpd_gpio; struct omap_dss_device dssdev; int /*<<< orphan*/  hpd_lock; int /*<<< orphan*/ * dev; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_HDMI ; 
 int OMAP_DSS_DEVICE_OP_DETECT ; 
 int OMAP_DSS_DEVICE_OP_HPD ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct gpio_desc* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct panel_drv_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  gpiod_to_irq (struct gpio_desc*) ; 
 int /*<<< orphan*/  hdmic_hpd_isr ; 
 int /*<<< orphan*/  hdmic_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omapdss_device_register (struct omap_dss_device*) ; 
 int /*<<< orphan*/  omapdss_display_init (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 

__attribute__((used)) static int hdmic_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	struct gpio_desc *gpio;
	int r;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);
	ddata->dev = &pdev->dev;

	mutex_init(&ddata->hpd_lock);

	/* HPD GPIO */
	gpio = devm_gpiod_get_optional(&pdev->dev, "hpd", GPIOD_IN);
	if (IS_ERR(gpio)) {
		dev_err(&pdev->dev, "failed to parse HPD gpio\n");
		return PTR_ERR(gpio);
	}

	ddata->hpd_gpio = gpio;

	if (ddata->hpd_gpio) {
		r = devm_request_threaded_irq(&pdev->dev,
				gpiod_to_irq(ddata->hpd_gpio),
				NULL, hdmic_hpd_isr,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
				IRQF_ONESHOT,
				"hdmic hpd", ddata);
		if (r)
			return r;
	}

	dssdev = &ddata->dssdev;
	dssdev->ops = &hdmic_ops;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_HDMI;
	dssdev->display = true;
	dssdev->owner = THIS_MODULE;
	dssdev->of_ports = BIT(0);
	dssdev->ops_flags = ddata->hpd_gpio
			  ? OMAP_DSS_DEVICE_OP_DETECT | OMAP_DSS_DEVICE_OP_HPD
			  : 0;

	omapdss_display_init(dssdev);
	omapdss_device_register(dssdev);

	return 0;
}