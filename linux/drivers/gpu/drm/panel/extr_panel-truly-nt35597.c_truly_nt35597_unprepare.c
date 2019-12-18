#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct truly_nt35597 {int prepared; int /*<<< orphan*/  dev; TYPE_1__** dsi; } ;
struct drm_panel {int dummy; } ;
struct TYPE_2__ {scalar_t__ mode_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MIPI_DCS_ENTER_SLEEP_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_OFF ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct truly_nt35597* panel_to_ctx (struct drm_panel*) ; 
 int truly_dcs_write (struct drm_panel*,int /*<<< orphan*/ ) ; 
 int truly_nt35597_power_off (struct truly_nt35597*) ; 

__attribute__((used)) static int truly_nt35597_unprepare(struct drm_panel *panel)
{
	struct truly_nt35597 *ctx = panel_to_ctx(panel);
	int ret = 0;

	if (!ctx->prepared)
		return 0;

	ctx->dsi[0]->mode_flags = 0;
	ctx->dsi[1]->mode_flags = 0;

	ret = truly_dcs_write(panel, MIPI_DCS_SET_DISPLAY_OFF);
	if (ret < 0) {
		DRM_DEV_ERROR(ctx->dev,
			"set_display_off cmd failed ret = %d\n",
			ret);
	}

	/* 120ms delay required here as per DCS spec */
	msleep(120);

	ret = truly_dcs_write(panel, MIPI_DCS_ENTER_SLEEP_MODE);
	if (ret < 0) {
		DRM_DEV_ERROR(ctx->dev,
			"enter_sleep cmd failed ret = %d\n", ret);
	}

	ret = truly_nt35597_power_off(ctx);
	if (ret < 0)
		DRM_DEV_ERROR(ctx->dev, "power_off failed ret = %d\n", ret);

	ctx->prepared = false;
	return ret;
}