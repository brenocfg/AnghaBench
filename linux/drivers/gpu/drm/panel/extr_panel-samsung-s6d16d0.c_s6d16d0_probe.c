#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct s6d16d0 {TYPE_1__ panel; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  supply; struct device* dev; } ;
struct device {int dummy; } ;
struct mipi_dsi_device {int lanes; int hs_rate; int lp_rate; int mode_flags; int /*<<< orphan*/  format; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MIPI_DSI_CLOCK_NON_CONTINUOUS ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int MIPI_DSI_MODE_EOT_PACKET ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct s6d16d0* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_remove (TYPE_1__*) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  mipi_dsi_set_drvdata (struct mipi_dsi_device*,struct s6d16d0*) ; 
 int /*<<< orphan*/  s6d16d0_drm_funcs ; 

__attribute__((used)) static int s6d16d0_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct s6d16d0 *s6;
	int ret;

	s6 = devm_kzalloc(dev, sizeof(struct s6d16d0), GFP_KERNEL);
	if (!s6)
		return -ENOMEM;

	mipi_dsi_set_drvdata(dsi, s6);
	s6->dev = dev;

	dsi->lanes = 2;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->hs_rate = 420160000;
	dsi->lp_rate = 19200000;
	/*
	 * This display uses command mode so no MIPI_DSI_MODE_VIDEO
	 * or MIPI_DSI_MODE_VIDEO_SYNC_PULSE
	 *
	 * As we only send commands we do not need to be continuously
	 * clocked.
	 */
	dsi->mode_flags =
		MIPI_DSI_CLOCK_NON_CONTINUOUS |
		MIPI_DSI_MODE_EOT_PACKET;

	s6->supply = devm_regulator_get(dev, "vdd1");
	if (IS_ERR(s6->supply))
		return PTR_ERR(s6->supply);

	/* This asserts RESET by default */
	s6->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						 GPIOD_OUT_HIGH);
	if (IS_ERR(s6->reset_gpio)) {
		ret = PTR_ERR(s6->reset_gpio);
		if (ret != -EPROBE_DEFER)
			DRM_DEV_ERROR(dev, "failed to request GPIO (%d)\n",
				      ret);
		return ret;
	}

	drm_panel_init(&s6->panel);
	s6->panel.dev = dev;
	s6->panel.funcs = &s6d16d0_drm_funcs;

	ret = drm_panel_add(&s6->panel);
	if (ret < 0)
		return ret;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0)
		drm_panel_remove(&s6->panel);

	return ret;
}