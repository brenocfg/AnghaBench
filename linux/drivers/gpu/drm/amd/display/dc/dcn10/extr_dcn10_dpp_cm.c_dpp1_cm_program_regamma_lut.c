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
struct pwl_result_data {int /*<<< orphan*/  delta_blue_reg; int /*<<< orphan*/  delta_green_reg; int /*<<< orphan*/  delta_red_reg; int /*<<< orphan*/  blue_reg; int /*<<< orphan*/  green_reg; int /*<<< orphan*/  red_reg; } ;
struct dpp {int dummy; } ;
struct dcn10_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_RGAM_LUT_DATA ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

void dpp1_cm_program_regamma_lut(struct dpp *dpp_base,
				 const struct pwl_result_data *rgb,
				 uint32_t num)
{
	uint32_t i;
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	for (i = 0 ; i < num; i++) {
		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].red_reg);
		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].green_reg);
		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].blue_reg);

		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].delta_red_reg);
		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].delta_green_reg);
		REG_SET(CM_RGAM_LUT_DATA, 0, CM_RGAM_LUT_DATA, rgb[i].delta_blue_reg);

	}

}