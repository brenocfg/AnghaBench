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
struct truly_nt35597 {int enabled; int /*<<< orphan*/  dev; scalar_t__ backlight; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int backlight_enable (scalar_t__) ; 
 struct truly_nt35597* panel_to_ctx (struct drm_panel*) ; 

__attribute__((used)) static int truly_nt35597_enable(struct drm_panel *panel)
{
	struct truly_nt35597 *ctx = panel_to_ctx(panel);
	int ret;

	if (ctx->enabled)
		return 0;

	if (ctx->backlight) {
		ret = backlight_enable(ctx->backlight);
		if (ret < 0)
			DRM_DEV_ERROR(ctx->dev, "backlight enable failed %d\n",
						  ret);
	}

	ctx->enabled = true;

	return 0;
}