#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  reset; int /*<<< orphan*/  power; } ;
struct rb070d30_panel {TYPE_2__ gpios; TYPE_1__* dsi; int /*<<< orphan*/  supply; } ;
struct drm_panel {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct rb070d30_panel* panel_to_rb070d30_panel (struct drm_panel*) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rb070d30_panel_prepare(struct drm_panel *panel)
{
	struct rb070d30_panel *ctx = panel_to_rb070d30_panel(panel);
	int ret;

	ret = regulator_enable(ctx->supply);
	if (ret < 0) {
		DRM_DEV_ERROR(&ctx->dsi->dev, "Failed to enable supply: %d\n", ret);
		return ret;
	}

	msleep(20);
	gpiod_set_value(ctx->gpios.power, 1);
	msleep(20);
	gpiod_set_value(ctx->gpios.reset, 1);
	msleep(20);
	return 0;
}