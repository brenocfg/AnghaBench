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
struct pwl_params {int /*<<< orphan*/  hw_points_num; int /*<<< orphan*/  rgb_resulted; } ;
struct dpp {int dummy; } ;
struct dcn20_dpp {int dummy; } ;
typedef  enum dc_lut_mode { ____Placeholder_dc_lut_mode } dc_lut_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CM_SHAPER_CONTROL ; 
 int /*<<< orphan*/  CM_SHAPER_LUT_MODE ; 
 int LUT_BYPASS ; 
 int LUT_RAM_A ; 
 int LUT_RAM_B ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 
 int /*<<< orphan*/  dpp20_configure_shaper_lut (struct dpp*,int) ; 
 int dpp20_get_shaper_current (struct dpp*) ; 
 int /*<<< orphan*/  dpp20_program_shaper_lut (struct dpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp20_program_shaper_luta_settings (struct dpp*,struct pwl_params const*) ; 
 int /*<<< orphan*/  dpp20_program_shaper_lutb_settings (struct dpp*,struct pwl_params const*) ; 

bool dpp20_program_shaper(
		struct dpp *dpp_base,
		const struct pwl_params *params)
{
	enum dc_lut_mode current_mode;
	enum dc_lut_mode next_mode;

	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	if (params == NULL) {
		REG_SET(CM_SHAPER_CONTROL, 0, CM_SHAPER_LUT_MODE, 0);
		return false;
	}
	current_mode = dpp20_get_shaper_current(dpp_base);

	if (current_mode == LUT_BYPASS || current_mode == LUT_RAM_A)
		next_mode = LUT_RAM_B;
	else
		next_mode = LUT_RAM_A;

	dpp20_configure_shaper_lut(dpp_base, next_mode == LUT_RAM_A ? true:false);

	if (next_mode == LUT_RAM_A)
		dpp20_program_shaper_luta_settings(dpp_base, params);
	else
		dpp20_program_shaper_lutb_settings(dpp_base, params);

	dpp20_program_shaper_lut(
			dpp_base, params->rgb_resulted, params->hw_points_num);

	REG_SET(CM_SHAPER_CONTROL, 0, CM_SHAPER_LUT_MODE, next_mode == LUT_RAM_A ? 1:2);

	return true;

}