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
typedef  scalar_t__ uint32_t ;
struct pwl_result_data {scalar_t__ red_reg; scalar_t__ green_reg; scalar_t__ blue_reg; scalar_t__ delta_red_reg; scalar_t__ delta_green_reg; scalar_t__ delta_blue_reg; } ;
struct pwl_params {scalar_t__ hw_points_num; struct pwl_result_data* rgb_resulted; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
struct dce_transform {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GAMMA_CORR_LUT_WRITE_EN_MASK ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,scalar_t__ const,scalar_t__) ; 
 scalar_t__ mmGAMMA_CORR_LUT_DATA ; 
 scalar_t__ const mmGAMMA_CORR_LUT_INDEX ; 
 scalar_t__ const mmGAMMA_CORR_LUT_WRITE_EN_MASK ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_pwl(struct dce_transform *xfm_dce,
		const struct pwl_params *params)
{
	uint32_t value = 0;

	set_reg_field_value(
		value,
		7,
		GAMMA_CORR_LUT_WRITE_EN_MASK,
		GAMMA_CORR_LUT_WRITE_EN_MASK);

	dm_write_reg(xfm_dce->base.ctx,
		mmGAMMA_CORR_LUT_WRITE_EN_MASK, value);

	dm_write_reg(xfm_dce->base.ctx,
		mmGAMMA_CORR_LUT_INDEX, 0);

	/* Program REGAMMA_LUT_DATA */
	{
		const uint32_t addr = mmGAMMA_CORR_LUT_DATA;
		uint32_t i = 0;
		const struct pwl_result_data *rgb =
				params->rgb_resulted;

		while (i != params->hw_points_num) {
			dm_write_reg(xfm_dce->base.ctx, addr, rgb->red_reg);
			dm_write_reg(xfm_dce->base.ctx, addr, rgb->green_reg);
			dm_write_reg(xfm_dce->base.ctx, addr, rgb->blue_reg);

			dm_write_reg(xfm_dce->base.ctx, addr,
				rgb->delta_red_reg);
			dm_write_reg(xfm_dce->base.ctx, addr,
				rgb->delta_green_reg);
			dm_write_reg(xfm_dce->base.ctx, addr,
				rgb->delta_blue_reg);

			++rgb;
			++i;
		}
	}
}