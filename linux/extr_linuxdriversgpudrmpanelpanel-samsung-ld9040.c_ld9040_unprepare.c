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
struct ld9040 {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_ENTER_SLEEP_MODE ; 
 int /*<<< orphan*/  MIPI_DCS_SET_DISPLAY_OFF ; 
 int /*<<< orphan*/  ld9040_clear_error (struct ld9040*) ; 
 int /*<<< orphan*/  ld9040_dcs_write_seq_static (struct ld9040*,int /*<<< orphan*/ ) ; 
 int ld9040_power_off (struct ld9040*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ld9040* panel_to_ld9040 (struct drm_panel*) ; 

__attribute__((used)) static int ld9040_unprepare(struct drm_panel *panel)
{
	struct ld9040 *ctx = panel_to_ld9040(panel);

	msleep(120);
	ld9040_dcs_write_seq_static(ctx, MIPI_DCS_SET_DISPLAY_OFF);
	ld9040_dcs_write_seq_static(ctx, MIPI_DCS_ENTER_SLEEP_MODE);
	msleep(40);

	ld9040_clear_error(ctx);

	return ld9040_power_off(ctx);
}