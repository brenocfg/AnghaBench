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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {void* vm; } ;
struct omap_dss_device {TYPE_1__ panel; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * driver; } ;
struct panel_drv_data {struct omap_dss_device dssdev; void* vm; int /*<<< orphan*/  hpd_gpio; int /*<<< orphan*/  hpd_lock; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_DIR_IN ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_HDMI ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct panel_drv_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct panel_drv_data*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 void* hdmic_default_vm ; 
 int /*<<< orphan*/  hdmic_driver ; 
 int /*<<< orphan*/  hdmic_hpd_isr ; 
 int hdmic_probe_of (struct platform_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int omapdss_register_display (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 

__attribute__((used)) static int hdmic_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	int r;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);
	ddata->dev = &pdev->dev;

	r = hdmic_probe_of(pdev);
	if (r)
		return r;

	mutex_init(&ddata->hpd_lock);

	if (gpio_is_valid(ddata->hpd_gpio)) {
		r = devm_gpio_request_one(&pdev->dev, ddata->hpd_gpio,
				GPIOF_DIR_IN, "hdmi_hpd");
		if (r)
			return r;

		r = devm_request_threaded_irq(&pdev->dev,
				gpio_to_irq(ddata->hpd_gpio),
				NULL, hdmic_hpd_isr,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING |
				IRQF_ONESHOT,
				"hdmic hpd", ddata);
		if (r)
			return r;
	}

	ddata->vm = hdmic_default_vm;

	dssdev = &ddata->dssdev;
	dssdev->driver = &hdmic_driver;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_HDMI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.vm = hdmic_default_vm;

	r = omapdss_register_display(dssdev);
	if (r) {
		dev_err(&pdev->dev, "Failed to register panel\n");
		return r;
	}

	return 0;
}