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
struct st7789v {int /*<<< orphan*/  power; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_ENTER_SLEEP_MODE ; 
 int /*<<< orphan*/  ST7789V_TEST (int,int /*<<< orphan*/ ) ; 
 struct st7789v* panel_to_st7789v (struct drm_panel*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st7789v_write_command (struct st7789v*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st7789v_unprepare(struct drm_panel *panel)
{
	struct st7789v *ctx = panel_to_st7789v(panel);
	int ret;

	ST7789V_TEST(ret, st7789v_write_command(ctx, MIPI_DCS_ENTER_SLEEP_MODE));

	regulator_disable(ctx->power);

	return 0;
}