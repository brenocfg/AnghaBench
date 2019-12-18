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
struct st7701_panel_desc {int num_supplies; scalar_t__ panel_sleep_delay; int /*<<< orphan*/ * supply_names; int /*<<< orphan*/  lanes; int /*<<< orphan*/  format; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/ * dev; int /*<<< orphan*/ * funcs; } ;
struct st7701 {struct st7701_panel_desc const* desc; struct mipi_dsi_device* dsi; TYPE_1__ panel; scalar_t__ sleep_delay; int /*<<< orphan*/  backlight; int /*<<< orphan*/  reset; TYPE_3__* supplies; } ;
struct mipi_dsi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  lanes; int /*<<< orphan*/  format; int /*<<< orphan*/  mode_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct st7701* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_of_find_backlight (int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  mipi_dsi_set_drvdata (struct mipi_dsi_device*,struct st7701*) ; 
 struct st7701_panel_desc* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st7701_funcs ; 

__attribute__((used)) static int st7701_dsi_probe(struct mipi_dsi_device *dsi)
{
	const struct st7701_panel_desc *desc;
	struct st7701 *st7701;
	int ret, i;

	st7701 = devm_kzalloc(&dsi->dev, sizeof(*st7701), GFP_KERNEL);
	if (!st7701)
		return -ENOMEM;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->mode_flags = desc->flags;
	dsi->format = desc->format;
	dsi->lanes = desc->lanes;

	st7701->supplies = devm_kcalloc(&dsi->dev, desc->num_supplies,
					sizeof(*st7701->supplies),
					GFP_KERNEL);
	if (!st7701->supplies)
		return -ENOMEM;

	for (i = 0; i < desc->num_supplies; i++)
		st7701->supplies[i].supply = desc->supply_names[i];

	ret = devm_regulator_bulk_get(&dsi->dev, desc->num_supplies,
				      st7701->supplies);
	if (ret < 0)
		return ret;

	st7701->reset = devm_gpiod_get(&dsi->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(st7701->reset)) {
		DRM_DEV_ERROR(&dsi->dev, "Couldn't get our reset GPIO\n");
		return PTR_ERR(st7701->reset);
	}

	st7701->backlight = devm_of_find_backlight(&dsi->dev);
	if (IS_ERR(st7701->backlight))
		return PTR_ERR(st7701->backlight);

	drm_panel_init(&st7701->panel);

	/**
	 * Once sleep out has been issued, ST7701 IC required to wait 120ms
	 * before initiating new commands.
	 *
	 * On top of that some panels might need an extra delay to wait, so
	 * add panel specific delay for those cases. As now this panel specific
	 * delay information is referenced from those panel BSP driver, example
	 * ts8550b and there is no valid documentation for that.
	 */
	st7701->sleep_delay = 120 + desc->panel_sleep_delay;
	st7701->panel.funcs = &st7701_funcs;
	st7701->panel.dev = &dsi->dev;

	ret = drm_panel_add(&st7701->panel);
	if (ret < 0)
		return ret;

	mipi_dsi_set_drvdata(dsi, st7701);
	st7701->dsi = dsi;
	st7701->desc = desc;

	return mipi_dsi_attach(dsi);
}