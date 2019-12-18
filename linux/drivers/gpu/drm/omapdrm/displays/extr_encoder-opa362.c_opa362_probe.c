#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct omap_dss_device {int of_ports; struct gpio_desc* next; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; TYPE_1__* dev; int /*<<< orphan*/ * ops; } ;
struct panel_drv_data {struct omap_dss_device dssdev; struct gpio_desc* enable_gpio; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  OMAP_DISPLAY_TYPE_VENC ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct gpio_desc* devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct panel_drv_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omapdss_device_register (struct omap_dss_device*) ; 
 struct gpio_desc* omapdss_of_find_connected_device (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opa362_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct panel_drv_data*) ; 

__attribute__((used)) static int opa362_probe(struct platform_device *pdev)
{
	struct panel_drv_data *ddata;
	struct omap_dss_device *dssdev;
	struct gpio_desc *gpio;

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
	dssdev->ops = &opa362_ops;
	dssdev->dev = &pdev->dev;
	dssdev->type = OMAP_DISPLAY_TYPE_VENC;
	dssdev->owner = THIS_MODULE;
	dssdev->of_ports = BIT(1) | BIT(0);

	dssdev->next = omapdss_of_find_connected_device(pdev->dev.of_node, 1);
	if (IS_ERR(dssdev->next)) {
		if (PTR_ERR(dssdev->next) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to find video sink\n");
		return PTR_ERR(dssdev->next);
	}

	omapdss_device_register(dssdev);

	return 0;
}