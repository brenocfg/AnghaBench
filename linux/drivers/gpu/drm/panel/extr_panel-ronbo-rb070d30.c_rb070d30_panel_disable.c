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
struct rb070d30_panel {int /*<<< orphan*/  dsi; int /*<<< orphan*/  backlight; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_disable (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_enter_sleep_mode (int /*<<< orphan*/ ) ; 
 struct rb070d30_panel* panel_to_rb070d30_panel (struct drm_panel*) ; 

__attribute__((used)) static int rb070d30_panel_disable(struct drm_panel *panel)
{
	struct rb070d30_panel *ctx = panel_to_rb070d30_panel(panel);

	backlight_disable(ctx->backlight);
	return mipi_dsi_dcs_enter_sleep_mode(ctx->dsi);
}