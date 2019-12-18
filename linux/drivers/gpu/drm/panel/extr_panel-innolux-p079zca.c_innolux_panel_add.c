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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct panel_desc {int num_supplies; int /*<<< orphan*/ * supply_names; } ;
struct device {int dummy; } ;
struct mipi_dsi_device {struct device dev; } ;
struct TYPE_5__ {struct device* dev; int /*<<< orphan*/ * funcs; } ;
struct innolux_panel {struct mipi_dsi_device* link; TYPE_1__ base; int /*<<< orphan*/ * backlight; int /*<<< orphan*/ * enable_gpio; TYPE_3__* supplies; struct panel_desc const* desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/ * devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct innolux_panel* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_of_find_backlight (struct device*) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_3__*) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  innolux_panel_funcs ; 
 int /*<<< orphan*/  mipi_dsi_set_drvdata (struct mipi_dsi_device*,struct innolux_panel*) ; 

__attribute__((used)) static int innolux_panel_add(struct mipi_dsi_device *dsi,
			     const struct panel_desc *desc)
{
	struct innolux_panel *innolux;
	struct device *dev = &dsi->dev;
	int err, i;

	innolux = devm_kzalloc(dev, sizeof(*innolux), GFP_KERNEL);
	if (!innolux)
		return -ENOMEM;

	innolux->desc = desc;

	innolux->supplies = devm_kcalloc(dev, desc->num_supplies,
					 sizeof(*innolux->supplies),
					 GFP_KERNEL);
	if (!innolux->supplies)
		return -ENOMEM;

	for (i = 0; i < desc->num_supplies; i++)
		innolux->supplies[i].supply = desc->supply_names[i];

	err = devm_regulator_bulk_get(dev, desc->num_supplies,
				      innolux->supplies);
	if (err < 0)
		return err;

	innolux->enable_gpio = devm_gpiod_get_optional(dev, "enable",
						       GPIOD_OUT_HIGH);
	if (IS_ERR(innolux->enable_gpio)) {
		err = PTR_ERR(innolux->enable_gpio);
		dev_dbg(dev, "failed to get enable gpio: %d\n", err);
		innolux->enable_gpio = NULL;
	}

	innolux->backlight = devm_of_find_backlight(dev);
	if (IS_ERR(innolux->backlight))
		return PTR_ERR(innolux->backlight);

	drm_panel_init(&innolux->base);
	innolux->base.funcs = &innolux_panel_funcs;
	innolux->base.dev = dev;

	err = drm_panel_add(&innolux->base);
	if (err < 0)
		return err;

	mipi_dsi_set_drvdata(dsi, innolux);
	innolux->link = dsi;

	return 0;
}