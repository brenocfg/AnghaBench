#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct transform {int dummy; } ;
struct scl_ratios_inits {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int alpha_en; } ;
struct TYPE_5__ {int /*<<< orphan*/  h_taps; int /*<<< orphan*/  v_taps; } ;
struct TYPE_4__ {int /*<<< orphan*/  horz; int /*<<< orphan*/  vert; } ;
struct scaler_data {TYPE_3__ lb_params; int /*<<< orphan*/  viewport; TYPE_2__ taps; TYPE_1__ ratios; } ;
struct dce_transform {int /*<<< orphan*/  const* filter_h; int /*<<< orphan*/  const* filter_v; int /*<<< orphan*/  lb_memory_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_EN ; 
 int /*<<< orphan*/  FILTER_TYPE_ALPHA_HORIZONTAL ; 
 int /*<<< orphan*/  FILTER_TYPE_ALPHA_VERTICAL ; 
 int /*<<< orphan*/  FILTER_TYPE_RGB_Y_HORIZONTAL ; 
 int /*<<< orphan*/  FILTER_TYPE_RGB_Y_VERTICAL ; 
 int /*<<< orphan*/  LB_DATA_FORMAT ; 
 int /*<<< orphan*/  LB_MEMORY_CONFIG ; 
 int /*<<< orphan*/  LB_MEMORY_CTRL ; 
 int /*<<< orphan*/  LB_MEMORY_SIZE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCL_COEF_UPDATE_COMPLETE ; 
 int /*<<< orphan*/  SCL_F_SHARP_CONTROL ; 
 int /*<<< orphan*/  SCL_HORZ_FILTER_CONTROL ; 
 int /*<<< orphan*/  SCL_H_2TAP_HARDCODE_COEF_EN ; 
 int /*<<< orphan*/  SCL_UPDATE ; 
 int /*<<< orphan*/  SCL_VERT_FILTER_CONTROL ; 
 int /*<<< orphan*/  SCL_V_2TAP_HARDCODE_COEF_EN ; 
 struct dce_transform* TO_DCE_TRANSFORM (struct transform*) ; 
 int /*<<< orphan*/  calculate_inits (struct dce_transform*,struct scaler_data const*,struct scl_ratios_inits*) ; 
 int /*<<< orphan*/ * get_filter_coeffs_16p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_multi_taps_filter (struct dce_transform*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_overscan (struct dce_transform*,struct scaler_data const*) ; 
 int /*<<< orphan*/  program_scl_ratios_inits (struct dce_transform*,struct scl_ratios_inits*) ; 
 int /*<<< orphan*/  program_viewport (struct dce_transform*,int /*<<< orphan*/ *) ; 
 int setup_scaling_configuration (struct dce_transform*,struct scaler_data const*) ; 

__attribute__((used)) static void dce_transform_set_scaler(
	struct transform *xfm,
	const struct scaler_data *data)
{
	struct dce_transform *xfm_dce = TO_DCE_TRANSFORM(xfm);
	bool is_scaling_required;
	bool filter_updated = false;
	const uint16_t *coeffs_v, *coeffs_h;

	/*Use all three pieces of memory always*/
	REG_SET_2(LB_MEMORY_CTRL, 0,
			LB_MEMORY_CONFIG, 0,
			LB_MEMORY_SIZE, xfm_dce->lb_memory_size);

	/* Clear SCL_F_SHARP_CONTROL value to 0 */
	REG_WRITE(SCL_F_SHARP_CONTROL, 0);

	/* 1. Program overscan */
	program_overscan(xfm_dce, data);

	/* 2. Program taps and configuration */
	is_scaling_required = setup_scaling_configuration(xfm_dce, data);

	if (is_scaling_required) {
		/* 3. Calculate and program ratio, filter initialization */
		struct scl_ratios_inits inits = { 0 };

		calculate_inits(xfm_dce, data, &inits);

		program_scl_ratios_inits(xfm_dce, &inits);

		coeffs_v = get_filter_coeffs_16p(data->taps.v_taps, data->ratios.vert);
		coeffs_h = get_filter_coeffs_16p(data->taps.h_taps, data->ratios.horz);

		if (coeffs_v != xfm_dce->filter_v || coeffs_h != xfm_dce->filter_h) {
			/* 4. Program vertical filters */
			if (xfm_dce->filter_v == NULL)
				REG_SET(SCL_VERT_FILTER_CONTROL, 0,
						SCL_V_2TAP_HARDCODE_COEF_EN, 0);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FILTER_TYPE_RGB_Y_VERTICAL);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.v_taps,
					coeffs_v,
					FILTER_TYPE_ALPHA_VERTICAL);

			/* 5. Program horizontal filters */
			if (xfm_dce->filter_h == NULL)
				REG_SET(SCL_HORZ_FILTER_CONTROL, 0,
						SCL_H_2TAP_HARDCODE_COEF_EN, 0);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FILTER_TYPE_RGB_Y_HORIZONTAL);
			program_multi_taps_filter(
					xfm_dce,
					data->taps.h_taps,
					coeffs_h,
					FILTER_TYPE_ALPHA_HORIZONTAL);

			xfm_dce->filter_v = coeffs_v;
			xfm_dce->filter_h = coeffs_h;
			filter_updated = true;
		}
	}

	/* 6. Program the viewport */
	program_viewport(xfm_dce, &data->viewport);

	/* 7. Set bit to flip to new coefficient memory */
	if (filter_updated)
		REG_UPDATE(SCL_UPDATE, SCL_COEF_UPDATE_COMPLETE, 1);

	REG_UPDATE(LB_DATA_FORMAT, ALPHA_EN, data->lb_params.alpha_en);
}