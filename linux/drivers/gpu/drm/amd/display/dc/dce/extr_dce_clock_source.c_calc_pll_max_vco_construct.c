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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ max_input_pxl_clk_pll_frequency; scalar_t__ min_input_pxl_clk_pll_frequency; int /*<<< orphan*/  max_output_pxl_clk_pll_frequency; int /*<<< orphan*/  min_output_pxl_clk_pll_frequency; int /*<<< orphan*/  crystal_frequency; } ;
struct dc_firmware_info {TYPE_2__ pll_info; } ;
struct calc_pll_clock_source_init_data {scalar_t__ max_override_input_pxl_clk_pll_freq_khz; scalar_t__ min_override_input_pxl_clk_pll_freq_khz; scalar_t__ num_fract_fb_divider_decimal_point; scalar_t__ num_fract_fb_divider_decimal_point_precision; int /*<<< orphan*/  max_pll_ref_divider; int /*<<< orphan*/  min_pll_ref_divider; int /*<<< orphan*/  max_pix_clk_pll_post_divider; int /*<<< orphan*/  min_pix_clk_pll_post_divider; int /*<<< orphan*/  ctx; TYPE_1__* bp; } ;
struct calc_pll_clock_source {scalar_t__ max_pll_input_freq_khz; scalar_t__ min_pll_input_freq_khz; scalar_t__ fract_fb_divider_decimal_points_num; scalar_t__ fract_fb_divider_precision; int fract_fb_divider_factor; int fract_fb_divider_precision_factor; int /*<<< orphan*/  max_pll_ref_divider; int /*<<< orphan*/  min_pll_ref_divider; int /*<<< orphan*/  max_pix_clock_pll_post_divider; int /*<<< orphan*/  min_pix_clock_pll_post_divider; int /*<<< orphan*/  max_vco_khz; int /*<<< orphan*/  min_vco_khz; int /*<<< orphan*/  ref_freq_khz; int /*<<< orphan*/  ctx; } ;
struct TYPE_3__ {struct dc_firmware_info fw_info; int /*<<< orphan*/  fw_info_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOG_ERROR (char*) ; 

__attribute__((used)) static bool calc_pll_max_vco_construct(
			struct calc_pll_clock_source *calc_pll_cs,
			struct calc_pll_clock_source_init_data *init_data)
{
	uint32_t i;
	struct dc_firmware_info *fw_info;
	if (calc_pll_cs == NULL ||
			init_data == NULL ||
			init_data->bp == NULL)
		return false;

	if (!init_data->bp->fw_info_valid)
		return false;

	fw_info = &init_data->bp->fw_info;
	calc_pll_cs->ctx = init_data->ctx;
	calc_pll_cs->ref_freq_khz = fw_info->pll_info.crystal_frequency;
	calc_pll_cs->min_vco_khz =
			fw_info->pll_info.min_output_pxl_clk_pll_frequency;
	calc_pll_cs->max_vco_khz =
			fw_info->pll_info.max_output_pxl_clk_pll_frequency;

	if (init_data->max_override_input_pxl_clk_pll_freq_khz != 0)
		calc_pll_cs->max_pll_input_freq_khz =
			init_data->max_override_input_pxl_clk_pll_freq_khz;
	else
		calc_pll_cs->max_pll_input_freq_khz =
			fw_info->pll_info.max_input_pxl_clk_pll_frequency;

	if (init_data->min_override_input_pxl_clk_pll_freq_khz != 0)
		calc_pll_cs->min_pll_input_freq_khz =
			init_data->min_override_input_pxl_clk_pll_freq_khz;
	else
		calc_pll_cs->min_pll_input_freq_khz =
			fw_info->pll_info.min_input_pxl_clk_pll_frequency;

	calc_pll_cs->min_pix_clock_pll_post_divider =
			init_data->min_pix_clk_pll_post_divider;
	calc_pll_cs->max_pix_clock_pll_post_divider =
			init_data->max_pix_clk_pll_post_divider;
	calc_pll_cs->min_pll_ref_divider =
			init_data->min_pll_ref_divider;
	calc_pll_cs->max_pll_ref_divider =
			init_data->max_pll_ref_divider;

	if (init_data->num_fract_fb_divider_decimal_point == 0 ||
		init_data->num_fract_fb_divider_decimal_point_precision >
				init_data->num_fract_fb_divider_decimal_point) {
		DC_LOG_ERROR(
			"The dec point num or precision is incorrect!");
		return false;
	}
	if (init_data->num_fract_fb_divider_decimal_point_precision == 0) {
		DC_LOG_ERROR(
			"Incorrect fract feedback divider precision num!");
		return false;
	}

	calc_pll_cs->fract_fb_divider_decimal_points_num =
				init_data->num_fract_fb_divider_decimal_point;
	calc_pll_cs->fract_fb_divider_precision =
			init_data->num_fract_fb_divider_decimal_point_precision;
	calc_pll_cs->fract_fb_divider_factor = 1;
	for (i = 0; i < calc_pll_cs->fract_fb_divider_decimal_points_num; ++i)
		calc_pll_cs->fract_fb_divider_factor *= 10;

	calc_pll_cs->fract_fb_divider_precision_factor = 1;
	for (
		i = 0;
		i < (calc_pll_cs->fract_fb_divider_decimal_points_num -
				calc_pll_cs->fract_fb_divider_precision);
		++i)
		calc_pll_cs->fract_fb_divider_precision_factor *= 10;

	return true;
}