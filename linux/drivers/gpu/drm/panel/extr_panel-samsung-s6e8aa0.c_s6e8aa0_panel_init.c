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
struct s6e8aa0 {int init_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DCS_EXIT_SLEEP_MODE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  s6e8aa0_apply_level_1_key (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_apply_level_2_key (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_brightness_set (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_dcs_write_seq_static (struct s6e8aa0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6e8aa0_display_condition_set (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_elvss_nvm_set (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_etc_elvss_control (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_etc_pentile_control (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_etc_power_control (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_etc_source_control (struct s6e8aa0*) ; 
 int /*<<< orphan*/  s6e8aa0_panel_cond_set (struct s6e8aa0*) ; 

__attribute__((used)) static void s6e8aa0_panel_init(struct s6e8aa0 *ctx)
{
	s6e8aa0_apply_level_1_key(ctx);
	s6e8aa0_apply_level_2_key(ctx);
	msleep(20);

	s6e8aa0_dcs_write_seq_static(ctx, MIPI_DCS_EXIT_SLEEP_MODE);
	msleep(40);

	s6e8aa0_panel_cond_set(ctx);
	s6e8aa0_display_condition_set(ctx);
	s6e8aa0_brightness_set(ctx);
	s6e8aa0_etc_source_control(ctx);
	s6e8aa0_etc_pentile_control(ctx);
	s6e8aa0_elvss_nvm_set(ctx);
	s6e8aa0_etc_power_control(ctx);
	s6e8aa0_etc_elvss_control(ctx);
	msleep(ctx->init_delay);
}