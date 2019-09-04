#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/ * funcs; TYPE_4__* dev; } ;
struct panel_lvds {TYPE_1__* backlight; TYPE_4__* dev; TYPE_2__ panel; int /*<<< orphan*/ * reset_gpio; int /*<<< orphan*/ * enable_gpio; int /*<<< orphan*/ * supply; } ;
struct device_node {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_4__*,struct panel_lvds*) ; 
 void* devm_gpiod_get_optional (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 struct panel_lvds* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (TYPE_4__*,char*) ; 
 int drm_panel_add (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_2__*) ; 
 TYPE_1__* of_find_backlight_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panel_lvds_funcs ; 
 int panel_lvds_parse_dt (struct panel_lvds*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int panel_lvds_probe(struct platform_device *pdev)
{
	struct panel_lvds *lvds;
	struct device_node *np;
	int ret;

	lvds = devm_kzalloc(&pdev->dev, sizeof(*lvds), GFP_KERNEL);
	if (!lvds)
		return -ENOMEM;

	lvds->dev = &pdev->dev;

	ret = panel_lvds_parse_dt(lvds);
	if (ret < 0)
		return ret;

	lvds->supply = devm_regulator_get_optional(lvds->dev, "power");
	if (IS_ERR(lvds->supply)) {
		ret = PTR_ERR(lvds->supply);

		if (ret != -ENODEV) {
			if (ret != -EPROBE_DEFER)
				dev_err(lvds->dev, "failed to request regulator: %d\n",
					ret);
			return ret;
		}

		lvds->supply = NULL;
	}

	/* Get GPIOs and backlight controller. */
	lvds->enable_gpio = devm_gpiod_get_optional(lvds->dev, "enable",
						     GPIOD_OUT_LOW);
	if (IS_ERR(lvds->enable_gpio)) {
		ret = PTR_ERR(lvds->enable_gpio);
		dev_err(lvds->dev, "failed to request %s GPIO: %d\n",
			"enable", ret);
		return ret;
	}

	lvds->reset_gpio = devm_gpiod_get_optional(lvds->dev, "reset",
						     GPIOD_OUT_HIGH);
	if (IS_ERR(lvds->reset_gpio)) {
		ret = PTR_ERR(lvds->reset_gpio);
		dev_err(lvds->dev, "failed to request %s GPIO: %d\n",
			"reset", ret);
		return ret;
	}

	np = of_parse_phandle(lvds->dev->of_node, "backlight", 0);
	if (np) {
		lvds->backlight = of_find_backlight_by_node(np);
		of_node_put(np);

		if (!lvds->backlight)
			return -EPROBE_DEFER;
	}

	/*
	 * TODO: Handle all power supplies specified in the DT node in a generic
	 * way for panels that don't care about power supply ordering. LVDS
	 * panels that require a specific power sequence will need a dedicated
	 * driver.
	 */

	/* Register the panel. */
	drm_panel_init(&lvds->panel);
	lvds->panel.dev = lvds->dev;
	lvds->panel.funcs = &panel_lvds_funcs;

	ret = drm_panel_add(&lvds->panel);
	if (ret < 0)
		goto error;

	dev_set_drvdata(lvds->dev, lvds);
	return 0;

error:
	put_device(&lvds->backlight->dev);
	return ret;
}