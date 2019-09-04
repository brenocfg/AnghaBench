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
typedef  size_t uint32_t ;
struct pp_clock_levels_with_latency {scalar_t__ num_levels; TYPE_2__* data; } ;
struct dm_pp_clock_levels_with_latency {scalar_t__ num_levels; TYPE_1__* data; } ;
typedef  enum dm_pp_clock_type { ____Placeholder_dm_pp_clock_type } dm_pp_clock_type ;
struct TYPE_4__ {int /*<<< orphan*/  latency_in_us; int /*<<< orphan*/  clocks_in_khz; } ;
struct TYPE_3__ {int /*<<< orphan*/  latency_in_us; int /*<<< orphan*/  clocks_in_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DECODE_PP_CLOCK_TYPE (int) ; 
 scalar_t__ DM_PP_MAX_CLOCK_LEVELS ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void pp_to_dc_clock_levels_with_latency(
		const struct pp_clock_levels_with_latency *pp_clks,
		struct dm_pp_clock_levels_with_latency *clk_level_info,
		enum dm_pp_clock_type dc_clk_type)
{
	uint32_t i;

	if (pp_clks->num_levels > DM_PP_MAX_CLOCK_LEVELS) {
		DRM_INFO("DM_PPLIB: Warning: %s clock: number of levels %d exceeds maximum of %d!\n",
				DC_DECODE_PP_CLOCK_TYPE(dc_clk_type),
				pp_clks->num_levels,
				DM_PP_MAX_CLOCK_LEVELS);

		clk_level_info->num_levels = DM_PP_MAX_CLOCK_LEVELS;
	} else
		clk_level_info->num_levels = pp_clks->num_levels;

	DRM_DEBUG("DM_PPLIB: values for %s clock\n",
			DC_DECODE_PP_CLOCK_TYPE(dc_clk_type));

	for (i = 0; i < clk_level_info->num_levels; i++) {
		DRM_DEBUG("DM_PPLIB:\t %d in kHz\n", pp_clks->data[i].clocks_in_khz);
		clk_level_info->data[i].clocks_in_khz = pp_clks->data[i].clocks_in_khz;
		clk_level_info->data[i].latency_in_us = pp_clks->data[i].latency_in_us;
	}
}