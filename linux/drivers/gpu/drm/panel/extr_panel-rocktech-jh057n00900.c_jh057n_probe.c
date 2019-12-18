#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct mipi_dsi_device {int lanes; int mode_flags; int /*<<< orphan*/  format; struct device dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct jh057n {TYPE_1__ panel; void* iovcc; void* vcc; void* backlight; struct device* dev; void* reset_gpio; } ;
struct TYPE_6__ {int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  hdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,...) ; 
 int /*<<< orphan*/  DRM_DEV_INFO (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int MIPI_DSI_MODE_VIDEO_BURST ; 
 int MIPI_DSI_MODE_VIDEO_SYNC_PULSE ; 
 int PTR_ERR (void*) ; 
 TYPE_4__ default_mode ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct jh057n* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* devm_of_find_backlight (struct device*) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 int /*<<< orphan*/  drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  jh057n_debugfs_init (struct jh057n*) ; 
 int /*<<< orphan*/  jh057n_drm_funcs ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dsi_set_drvdata (struct mipi_dsi_device*,struct jh057n*) ; 

__attribute__((used)) static int jh057n_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct jh057n *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->reset_gpio)) {
		DRM_DEV_ERROR(dev, "cannot get reset gpio\n");
		return PTR_ERR(ctx->reset_gpio);
	}

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO |
		MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_MODE_VIDEO_SYNC_PULSE;

	ctx->backlight = devm_of_find_backlight(dev);
	if (IS_ERR(ctx->backlight))
		return PTR_ERR(ctx->backlight);

	ctx->vcc = devm_regulator_get(dev, "vcc");
	if (IS_ERR(ctx->vcc)) {
		ret = PTR_ERR(ctx->vcc);
		if (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev,
				      "Failed to request vcc regulator: %d\n",
				      ret);
		return ret;
	}
	ctx->iovcc = devm_regulator_get(dev, "iovcc");
	if (IS_ERR(ctx->iovcc)) {
		ret = PTR_ERR(ctx->iovcc);
		if (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev,
				      "Failed to request iovcc regulator: %d\n",
				      ret);
		return ret;
	}

	drm_panel_init(&ctx->panel);
	ctx->panel.dev = dev;
	ctx->panel.funcs = &jh057n_drm_funcs;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		DRM_DEV_ERROR(dev,
			      "mipi_dsi_attach failed (%d). Is host ready?\n",
			      ret);
		drm_panel_remove(&ctx->panel);
		return ret;
	}

	DRM_DEV_INFO(dev, "%ux%u@%u %ubpp dsi %udl - ready\n",
		     default_mode.hdisplay, default_mode.vdisplay,
		     default_mode.vrefresh,
		     mipi_dsi_pixel_format_to_bpp(dsi->format), dsi->lanes);

	jh057n_debugfs_init(ctx);
	return 0;
}