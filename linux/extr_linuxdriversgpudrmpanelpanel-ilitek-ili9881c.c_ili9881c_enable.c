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
struct ili9881c {int /*<<< orphan*/  backlight; int /*<<< orphan*/  dsi; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dsi_dcs_set_display_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ili9881c* panel_to_ili9881c (struct drm_panel*) ; 

__attribute__((used)) static int ili9881c_enable(struct drm_panel *panel)
{
	struct ili9881c *ctx = panel_to_ili9881c(panel);

	msleep(120);

	mipi_dsi_dcs_set_display_on(ctx->dsi);
	backlight_enable(ctx->backlight);

	return 0;
}