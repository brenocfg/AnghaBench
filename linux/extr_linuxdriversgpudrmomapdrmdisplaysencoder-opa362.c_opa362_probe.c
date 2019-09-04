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
struct TYPE_2__ {int /*<<< orphan*/ * atv; } ;
struct omap_dss_device {int /*<<< orphan*/  owner; void* output_type; void* type; int /*<<< orphan*/ * dev; TYPE_1__ ops; } ;
struct panel_drv_data {struct omap_dss_device dssdev; struct gpio_desc* enable_gpio; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 void* OMAP_DISPLAY_TYPE_VENC ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct gpio_desc* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct panel_drv_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int omapdss_register_output (struct omap_dss_device*) ; 
 int /*<<< orphan*/  opa362_atv_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 

__attribute__((used)) static int opa362_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	struct gpio_desc *gpio;
	int r;

	dev_dbg(&pdev->dev, "probe\n");

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	platform_set_drvdata(pdev, ddata);

	gpio = devm_gpiod_get_optional(&pdev->dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(gpio))
		return PTR_ERR(gpio);

	ddata->enable_gpio = gpio;

	dssdev = &ddata->dssdev;
	dssdev->ops.atv = &opa362_atv_ops;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_VENC;
	dssdev->output_type = OMAP_DISPLAY_TYPE_VENC;
	dssdev->owner = THIS_MODULE;

	r = omapdss_register_output(dssdev);
	if (r) {
		dev_err(&pdev->dev, "Failed to register output\n");
		return r;
	}

	return 0;
}