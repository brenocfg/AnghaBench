#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct jh057n {int prepared; int /*<<< orphan*/  vcc; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  iovcc; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_DRIVER (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct jh057n* panel_to_jh057n (struct drm_panel*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int jh057n_prepare(struct drm_panel *panel)
{
	struct jh057n *ctx = panel_to_jh057n(panel);
	int ret;

	if (ctx->prepared)
		return 0;

	DRM_DEV_DEBUG_DRIVER(ctx->dev, "Resetting the panel\n");
	ret = regulator_enable(ctx->vcc);
	if (ret < 0) {
		DRM_DEV_ERROR(ctx->dev,
			      "Failed to enable vcc supply: %d\n", ret);
		return ret;
	}
	ret = regulator_enable(ctx->iovcc);
	if (ret < 0) {
		DRM_DEV_ERROR(ctx->dev,
			      "Failed to enable iovcc supply: %d\n", ret);
		goto disable_vcc;
	}

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(20, 40);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);

	ctx->prepared = true;

	return 0;

disable_vcc:
	regulator_disable(ctx->vcc);
	return ret;
}