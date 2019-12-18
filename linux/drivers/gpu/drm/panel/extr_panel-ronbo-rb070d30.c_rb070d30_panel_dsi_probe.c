#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * funcs; int /*<<< orphan*/ * dev; } ;
struct TYPE_4__ {void* shlr; void* updn; void* power; void* reset; } ;
struct rb070d30_panel {TYPE_2__ panel; void* backlight; TYPE_1__ gpios; struct mipi_dsi_device* dsi; void* supply; } ;
struct mipi_dsi_device {int mode_flags; int lanes; int /*<<< orphan*/  format; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int MIPI_DSI_MODE_LPM ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int MIPI_DSI_MODE_VIDEO_BURST ; 
 int PTR_ERR (void*) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct rb070d30_panel* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_of_find_backlight (int /*<<< orphan*/ *) ; 
 void* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int drm_panel_add (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_2__*) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  mipi_dsi_set_drvdata (struct mipi_dsi_device*,struct rb070d30_panel*) ; 
 int /*<<< orphan*/  rb070d30_panel_funcs ; 

__attribute__((used)) static int rb070d30_panel_dsi_probe(struct mipi_dsi_device *dsi)
{
	struct rb070d30_panel *ctx;
	int ret;

	ctx = devm_kzalloc(&dsi->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->supply = devm_regulator_get(&dsi->dev, "vcc-lcd");
	if (IS_ERR(ctx->supply))
		return PTR_ERR(ctx->supply);

	mipi_dsi_set_drvdata(dsi, ctx);
	ctx->dsi = dsi;

	drm_panel_init(&ctx->panel);
	ctx->panel.dev = &dsi->dev;
	ctx->panel.funcs = &rb070d30_panel_funcs;

	ctx->gpios.reset = devm_gpiod_get(&dsi->dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->gpios.reset)) {
		DRM_DEV_ERROR(&dsi->dev, "Couldn't get our reset GPIO\n");
		return PTR_ERR(ctx->gpios.reset);
	}

	ctx->gpios.power = devm_gpiod_get(&dsi->dev, "power", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->gpios.power)) {
		DRM_DEV_ERROR(&dsi->dev, "Couldn't get our power GPIO\n");
		return PTR_ERR(ctx->gpios.power);
	}

	/*
	 * We don't change the state of that GPIO later on but we need
	 * to force it into a low state.
	 */
	ctx->gpios.updn = devm_gpiod_get(&dsi->dev, "updn", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->gpios.updn)) {
		DRM_DEV_ERROR(&dsi->dev, "Couldn't get our updn GPIO\n");
		return PTR_ERR(ctx->gpios.updn);
	}

	/*
	 * We don't change the state of that GPIO later on but we need
	 * to force it into a low state.
	 */
	ctx->gpios.shlr = devm_gpiod_get(&dsi->dev, "shlr", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->gpios.shlr)) {
		DRM_DEV_ERROR(&dsi->dev, "Couldn't get our shlr GPIO\n");
		return PTR_ERR(ctx->gpios.shlr);
	}

	ctx->backlight = devm_of_find_backlight(&dsi->dev);
	if (IS_ERR(ctx->backlight)) {
		DRM_DEV_ERROR(&dsi->dev, "Couldn't get our backlight\n");
		return PTR_ERR(ctx->backlight);
	}

	ret = drm_panel_add(&ctx->panel);
	if (ret < 0)
		return ret;

	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_MODE_LPM;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->lanes = 4;

	return mipi_dsi_attach(dsi);
}