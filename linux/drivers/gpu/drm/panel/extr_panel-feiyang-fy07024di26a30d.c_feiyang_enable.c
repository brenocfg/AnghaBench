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
struct feiyang {int /*<<< orphan*/  backlight; int /*<<< orphan*/  dsi; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mipi_dsi_dcs_set_display_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct feiyang* panel_to_feiyang (struct drm_panel*) ; 

__attribute__((used)) static int feiyang_enable(struct drm_panel *panel)
{
	struct feiyang *ctx = panel_to_feiyang(panel);

	/* T12 (video & logic signal rise + backlight rise) T12 >= 200ms */
	msleep(200);

	mipi_dsi_dcs_set_display_on(ctx->dsi);
	backlight_enable(ctx->backlight);

	return 0;
}