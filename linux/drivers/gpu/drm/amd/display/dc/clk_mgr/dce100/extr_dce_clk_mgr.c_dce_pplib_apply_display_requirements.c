#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dm_pp_display_configuration {int /*<<< orphan*/  avail_mclk_switch_time_us; } ;
struct dc_state {struct dm_pp_display_configuration pp_display_cfg; } ;
struct dc {int /*<<< orphan*/  ctx; TYPE_1__* current_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  pp_display_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce110_fill_display_configs (struct dc_state*,struct dm_pp_display_configuration*) ; 
 int /*<<< orphan*/  dce110_get_min_vblank_time_us (struct dc_state*) ; 
 int /*<<< orphan*/  dm_pp_apply_display_requirements (int /*<<< orphan*/ ,struct dm_pp_display_configuration*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct dm_pp_display_configuration*,int) ; 

__attribute__((used)) static void dce_pplib_apply_display_requirements(
	struct dc *dc,
	struct dc_state *context)
{
	struct dm_pp_display_configuration *pp_display_cfg = &context->pp_display_cfg;

	pp_display_cfg->avail_mclk_switch_time_us = dce110_get_min_vblank_time_us(context);

	dce110_fill_display_configs(context, pp_display_cfg);

	if (memcmp(&dc->current_state->pp_display_cfg, pp_display_cfg, sizeof(*pp_display_cfg)) !=  0)
		dm_pp_apply_display_requirements(dc->ctx, pp_display_cfg);
}