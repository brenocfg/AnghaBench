#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct s6e8aa0 {TYPE_1__ panel; scalar_t__ brightness; int /*<<< orphan*/  reset_gpio; TYPE_4__* supplies; struct device* dev; } ;
struct device {int dummy; } ;
struct mipi_dsi_device {int lanes; int mode_flags; int /*<<< orphan*/  format; struct device dev; } ;
struct TYPE_7__ {char* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_4__*) ; 
 int ENOMEM ; 
 scalar_t__ GAMMA_LEVEL_NUM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int MIPI_DSI_MODE_EOT_PACKET ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int MIPI_DSI_MODE_VIDEO_AUTO_VERT ; 
 int MIPI_DSI_MODE_VIDEO_BURST ; 
 int MIPI_DSI_MODE_VIDEO_HBP ; 
 int MIPI_DSI_MODE_VIDEO_HFP ; 
 int MIPI_DSI_MODE_VIDEO_HSA ; 
 int MIPI_DSI_MODE_VSYNC_FLUSH ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct s6e8aa0* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_remove (TYPE_1__*) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  mipi_dsi_set_drvdata (struct mipi_dsi_device*,struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_drm_funcs ; 
 int s6e8aa0_parse_dt (struct s6e8aa0*) ; 

__attribute__((used)) static int s6e8aa0_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct s6e8aa0 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(struct s6e8aa0), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->dev = dev;

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST
		| MIPI_DSI_MODE_VIDEO_HFP | MIPI_DSI_MODE_VIDEO_HBP
		| MIPI_DSI_MODE_VIDEO_HSA | MIPI_DSI_MODE_EOT_PACKET
		| MIPI_DSI_MODE_VSYNC_FLUSH | MIPI_DSI_MODE_VIDEO_AUTO_VERT;

	ret = s6e8aa0_parse_dt(ctx);
	if (ret < 0)
		return ret;

	ctx->supplies[0].supply = "vdd3";
	ctx->supplies[1].supply = "vci";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "failed to get regulators: %d\n", ret);
		return ret;
	}

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio)) {
		dev_err(dev, "cannot get reset-gpios %ld\n",
			PTR_ERR(ctx->reset_gpio));
		return PTR_ERR(ctx->reset_gpio);
	}

	ctx->brightness = GAMMA_LEVEL_NUM - 1;

	drm_panel_init(&ctx->panel);
	ctx->panel.dev = dev;
	ctx->panel.funcs = &s6e8aa0_drm_funcs;

	ret = drm_panel_add(&ctx->panel);
	if (ret < 0)
		return ret;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0)
		drm_panel_remove(&ctx->panel);

	return ret;
}