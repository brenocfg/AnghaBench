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
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct panel_drv_data {int /*<<< orphan*/  vm; struct gpio_desc* backlight; struct gpio_desc* vcc_supply; struct gpio_desc* enable_gpio; } ;
struct gpio_desc {int dummy; } ;
struct display_timing {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct gpio_desc* devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_of_find_backlight (TYPE_1__*) ; 
 struct gpio_desc* devm_regulator_get (TYPE_1__*,char*) ; 
 int of_get_display_timing (struct device_node*,char*,struct display_timing*) ; 
 struct panel_drv_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  videomode_from_timing (struct display_timing*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int panel_dpi_probe_of(struct platform_device *pdev)
{
	struct panel_drv_data *ddata = platform_get_drvdata(pdev);
	struct device_node *node = pdev->dev.of_node;
	int r;
	struct display_timing timing;
	struct gpio_desc *gpio;

	gpio = devm_gpiod_get_optional(&pdev->dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(gpio))
		return PTR_ERR(gpio);

	ddata->enable_gpio = gpio;

	/*
	 * Many different panels are supported by this driver and there are
	 * probably very different needs for their reset pins in regards to
	 * timing and order relative to the enable gpio. So for now it's just
	 * ensured that the reset line isn't active.
	 */
	gpio = devm_gpiod_get_optional(&pdev->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(gpio))
		return PTR_ERR(gpio);

	ddata->vcc_supply = devm_regulator_get(&pdev->dev, "vcc");
	if (IS_ERR(ddata->vcc_supply))
		return PTR_ERR(ddata->vcc_supply);

	ddata->backlight = devm_of_find_backlight(&pdev->dev);

	if (IS_ERR(ddata->backlight))
		return PTR_ERR(ddata->backlight);

	r = of_get_display_timing(node, "panel-timing", &timing);
	if (r) {
		dev_err(&pdev->dev, "failed to get video timing\n");
		return r;
	}

	videomode_from_timing(&timing, &ddata->vm);

	return 0;
}