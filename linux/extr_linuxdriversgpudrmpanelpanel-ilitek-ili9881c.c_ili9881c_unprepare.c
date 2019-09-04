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
struct ili9881c {int /*<<< orphan*/  reset; int /*<<< orphan*/  power; int /*<<< orphan*/  dsi; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mipi_dsi_dcs_enter_sleep_mode (int /*<<< orphan*/ ) ; 
 struct ili9881c* panel_to_ili9881c (struct drm_panel*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ili9881c_unprepare(struct drm_panel *panel)
{
	struct ili9881c *ctx = panel_to_ili9881c(panel);

	mipi_dsi_dcs_enter_sleep_mode(ctx->dsi);
	regulator_disable(ctx->power);
	gpiod_set_value(ctx->reset, 1);

	return 0;
}