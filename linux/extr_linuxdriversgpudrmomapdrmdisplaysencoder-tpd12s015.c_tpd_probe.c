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
struct TYPE_2__ {int /*<<< orphan*/ * hdmi; } ;
struct omap_dss_device {int port_num; int /*<<< orphan*/  owner; void* output_type; void* type; int /*<<< orphan*/ * dev; TYPE_1__ ops; } ;
struct panel_drv_data {struct omap_dss_device* in; struct omap_dss_device dssdev; struct gpio_desc* hpd_gpio; int /*<<< orphan*/  hpd_lock; struct gpio_desc* ls_oe_gpio; struct gpio_desc* ct_cp_hpd_gpio; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 void* OMAP_DISPLAY_TYPE_HDMI ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct gpio_desc* devm_gpiod_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_gpiod_get_index_optional (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct panel_drv_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  gpiod_to_irq (struct gpio_desc*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int omapdss_register_output (struct omap_dss_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 
 int /*<<< orphan*/  tpd_hdmi_ops ; 
 int /*<<< orphan*/  tpd_hpd_isr ; 

__attribute__((used)) static int tpd_probe(struct platform_device *pdev)
{
	struct omap_dss_device *in, *dssdev;
	struct panel_drv_data *ddata;
	int r;
	struct gpio_desc *gpio;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);

	gpio = devm_gpiod_get_index_optional(&pdev->dev, NULL, 0,
		 GPIOD_OUT_LOW);
	if (IS_ERR(gpio))
		return PTR_ERR(gpio);

	ddata->ct_cp_hpd_gpio = gpio;

	gpio = devm_gpiod_get_index_optional(&pdev->dev, NULL, 1,
		 GPIOD_OUT_LOW);
	if (IS_ERR(gpio))
		return PTR_ERR(gpio);

	ddata->ls_oe_gpio = gpio;

	gpio = devm_gpiod_get_index(&pdev->dev, NULL, 2,
		GPIOD_IN);
	if (IS_ERR(gpio))
		return PTR_ERR(gpio);

	ddata->hpd_gpio = gpio;

	mutex_init(&ddata->hpd_lock);

	r = devm_request_threaded_irq(&pdev->dev, gpiod_to_irq(ddata->hpd_gpio),
		NULL, tpd_hpd_isr,
		IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
		"tpd12s015 hpd", ddata);
	if (r)
		return r;

	dssdev = &ddata->dssdev;
	dssdev->ops.hdmi = &tpd_hdmi_ops;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_HDMI;
	dssdev->output_type = OMAP_DISPLAY_TYPE_HDMI;
	dssdev->owner = THIS_MODULE;
	dssdev->port_num = 1;

	in = ddata->in;

	r = omapdss_register_output(dssdev);
	if (r) {
		dev_err(&pdev->dev, "Failed to register output\n");
		return r;
	}

	return 0;
}