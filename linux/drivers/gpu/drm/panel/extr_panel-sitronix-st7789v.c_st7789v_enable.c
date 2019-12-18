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
struct st7789v {TYPE_2__* backlight; } ;
struct drm_panel {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  power; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_CORE_FBBLANK ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_ON ; 
 int /*<<< orphan*/  backlight_update_status (TYPE_2__*) ; 
 struct st7789v* panel_to_st7789v (struct drm_panel*) ; 
 int st7789v_write_command (struct st7789v*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st7789v_enable(struct drm_panel *panel)
{
	struct st7789v *ctx = panel_to_st7789v(panel);

	if (ctx->backlight) {
		ctx->backlight->props.state &= ~BL_CORE_FBBLANK;
		ctx->backlight->props.power = FB_BLANK_UNBLANK;
		backlight_update_status(ctx->backlight);
	}

	return st7789v_write_command(ctx, MIPI_DCS_SET_DISPLAY_ON);
}