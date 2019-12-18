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
struct s6e63m0 {int enabled; int /*<<< orphan*/  bl_dev; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_ENTER_SLEEP_MODE ; 
 int /*<<< orphan*/  backlight_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct s6e63m0* panel_to_s6e63m0 (struct drm_panel*) ; 
 int /*<<< orphan*/  s6e63m0_dcs_write_seq_static (struct s6e63m0*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s6e63m0_disable(struct drm_panel *panel)
{
	struct s6e63m0 *ctx = panel_to_s6e63m0(panel);

	if (!ctx->enabled)
		return 0;

	backlight_disable(ctx->bl_dev);

	s6e63m0_dcs_write_seq_static(ctx, MIPI_DCS_ENTER_SLEEP_MODE);
	msleep(200);

	ctx->enabled = false;

	return 0;
}