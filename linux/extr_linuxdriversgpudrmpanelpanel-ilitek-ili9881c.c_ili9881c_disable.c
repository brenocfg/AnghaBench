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
struct ili9881c {int /*<<< orphan*/  dsi; int /*<<< orphan*/  backlight; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_disable (int /*<<< orphan*/ ) ; 
 int mipi_dsi_dcs_set_display_off (int /*<<< orphan*/ ) ; 
 struct ili9881c* panel_to_ili9881c (struct drm_panel*) ; 

__attribute__((used)) static int ili9881c_disable(struct drm_panel *panel)
{
	struct ili9881c *ctx = panel_to_ili9881c(panel);

	backlight_disable(ctx->backlight);
	return mipi_dsi_dcs_set_display_off(ctx->dsi);
}