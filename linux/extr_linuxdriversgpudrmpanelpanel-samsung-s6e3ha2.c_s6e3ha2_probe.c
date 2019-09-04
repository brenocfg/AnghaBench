#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct s6e3ha2 {TYPE_6__* bl_dev; TYPE_2__ panel; TYPE_6__* enable_gpio; TYPE_6__* reset_gpio; TYPE_5__* supplies; int /*<<< orphan*/  desc; struct device* dev; } ;
struct device {int dummy; } ;
struct mipi_dsi_device {int lanes; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  format; struct device dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  power; int /*<<< orphan*/  brightness; int /*<<< orphan*/  max_brightness; } ;
struct TYPE_14__ {TYPE_1__ props; } ;
struct TYPE_13__ {char* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_5__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (TYPE_6__*) ; 
 int /*<<< orphan*/  MIPI_DSI_CLOCK_NON_CONTINUOUS ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int PTR_ERR (TYPE_6__*) ; 
 int /*<<< orphan*/  S6E3HA2_DEFAULT_BRIGHTNESS ; 
 int /*<<< orphan*/  S6E3HA2_MAX_BRIGHTNESS ; 
 TYPE_6__* backlight_device_register (char*,struct device*,struct s6e3ha2*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlight_device_unregister (TYPE_6__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct s6e3ha2* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int drm_panel_add (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_panel_remove (TYPE_2__*) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  mipi_dsi_set_drvdata (struct mipi_dsi_device*,struct s6e3ha2*) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  s6e3ha2_bl_ops ; 
 int /*<<< orphan*/  s6e3ha2_drm_funcs ; 

__attribute__((used)) static int s6e3ha2_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct s6e3ha2 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;
	ctx->desc = of_device_get_match_data(dev);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_CLOCK_NON_CONTINUOUS;

	ctx->supplies[0].supply = "vdd3";
	ctx->supplies[1].supply = "vci";

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "failed to get regulators: %d\n", ret);
		return ret;
	}

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->reset_gpio)) {
		dev_err(dev, "cannot get reset-gpios %ld\n",
			PTR_ERR(ctx->reset_gpio));
		return PTR_ERR(ctx->reset_gpio);
	}

	ctx->enable_gpio = devm_gpiod_get(dev, "enable", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->enable_gpio)) {
		dev_err(dev, "cannot get enable-gpios %ld\n",
			PTR_ERR(ctx->enable_gpio));
		return PTR_ERR(ctx->enable_gpio);
	}

	ctx->bl_dev = backlight_device_register("s6e3ha2", dev, ctx,
						&s6e3ha2_bl_ops, NULL);
	if (IS_ERR(ctx->bl_dev)) {
		dev_err(dev, "failed to register backlight device\n");
		return PTR_ERR(ctx->bl_dev);
	}

	ctx->bl_dev->props.max_brightness = S6E3HA2_MAX_BRIGHTNESS;
	ctx->bl_dev->props.brightness = S6E3HA2_DEFAULT_BRIGHTNESS;
	ctx->bl_dev->props.power = FB_BLANK_POWERDOWN;

	drm_panel_init(&ctx->panel);
	ctx->panel.dev = dev;
	ctx->panel.funcs = &s6e3ha2_drm_funcs;

	ret = drm_panel_add(&ctx->panel);
	if (ret < 0)
		goto unregister_backlight;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0)
		goto remove_panel;

	return ret;

remove_panel:
	drm_panel_remove(&ctx->panel);

unregister_backlight:
	backlight_device_unregister(ctx->bl_dev);

	return ret;
}