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
typedef  size_t uint32_t ;
struct pwl_result_data {size_t red_reg; size_t green_reg; size_t blue_reg; size_t delta_red_reg; size_t delta_green_reg; size_t delta_blue_reg; } ;
struct dpp {int dummy; } ;
struct dcn20_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_SHAPER_LUT_DATA ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp20_program_shaper_lut(
		struct dpp *dpp_base,
		const struct pwl_result_data *rgb,
		uint32_t num)
{
	uint32_t i, red, green, blue;
	uint32_t  red_delta, green_delta, blue_delta;
	uint32_t  red_value, green_value, blue_value;

	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	for (i = 0 ; i < num; i++) {

		red   = rgb[i].red_reg;
		green = rgb[i].green_reg;
		blue  = rgb[i].blue_reg;

		red_delta   = rgb[i].delta_red_reg;
		green_delta = rgb[i].delta_green_reg;
		blue_delta  = rgb[i].delta_blue_reg;

		red_value   = ((red_delta   & 0x3ff) << 14) | (red   & 0x3fff);
		green_value = ((green_delta & 0x3ff) << 14) | (green & 0x3fff);
		blue_value  = ((blue_delta  & 0x3ff) << 14) | (blue  & 0x3fff);

		REG_SET(CM_SHAPER_LUT_DATA, 0, CM_SHAPER_LUT_DATA, red_value);
		REG_SET(CM_SHAPER_LUT_DATA, 0, CM_SHAPER_LUT_DATA, green_value);
		REG_SET(CM_SHAPER_LUT_DATA, 0, CM_SHAPER_LUT_DATA, blue_value);
	}

}