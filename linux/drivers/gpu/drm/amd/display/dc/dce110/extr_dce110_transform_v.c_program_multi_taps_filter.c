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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {struct dc_context* ctx; } ;
struct dce_transform {TYPE_1__ base; } ;
struct dc_context {int dummy; } ;
typedef  enum ram_filter_type { ____Placeholder_ram_filter_type } ram_filter_type ;

/* Variables and functions */
 int /*<<< orphan*/  DCFEV_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  DCFEV_MEM_PWR_STATUS ; 
 int /*<<< orphan*/  SCLV_COEFF_MEM_PWR_DIS ; 
 int /*<<< orphan*/  SCLV_COEFF_MEM_PWR_STATE ; 
 int /*<<< orphan*/  SCLV_COEF_RAM_SELECT ; 
 int /*<<< orphan*/  SCLV_COEF_RAM_TAP_DATA ; 
 int SCLV_PHASES ; 
 int /*<<< orphan*/  SCL_C_RAM_EVEN_TAP_COEF ; 
 int /*<<< orphan*/  SCL_C_RAM_EVEN_TAP_COEF_EN ; 
 int /*<<< orphan*/  SCL_C_RAM_FILTER_TYPE ; 
 int /*<<< orphan*/  SCL_C_RAM_ODD_TAP_COEF ; 
 int /*<<< orphan*/  SCL_C_RAM_ODD_TAP_COEF_EN ; 
 int /*<<< orphan*/  SCL_C_RAM_PHASE ; 
 int /*<<< orphan*/  SCL_C_RAM_TAP_PAIR_IDX ; 
 int /*<<< orphan*/  dm_read_reg (struct dc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_field_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmDCFEV_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  mmDCFEV_MEM_PWR_STATUS ; 
 int /*<<< orphan*/  mmSCLV_COEF_RAM_SELECT ; 
 int /*<<< orphan*/  mmSCLV_COEF_RAM_TAP_DATA ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void program_multi_taps_filter(
	struct dce_transform *xfm_dce,
	int taps,
	const uint16_t *coeffs,
	enum ram_filter_type filter_type)
{
	struct dc_context *ctx = xfm_dce->base.ctx;
	int i, phase, pair;
	int array_idx = 0;
	int taps_pairs = (taps + 1) / 2;
	int phases_to_program = SCLV_PHASES / 2 + 1;

	uint32_t select = 0;
	uint32_t power_ctl, power_ctl_off;

	if (!coeffs)
		return;

	/*We need to disable power gating on coeff memory to do programming*/
	power_ctl = dm_read_reg(ctx, mmDCFEV_MEM_PWR_CTRL);
	power_ctl_off = power_ctl;
	set_reg_field_value(power_ctl_off, 1, DCFEV_MEM_PWR_CTRL, SCLV_COEFF_MEM_PWR_DIS);
	dm_write_reg(ctx, mmDCFEV_MEM_PWR_CTRL, power_ctl_off);

	/*Wait to disable gating:*/
	for (i = 0; i < 10; i++) {
		if (get_reg_field_value(
				dm_read_reg(ctx, mmDCFEV_MEM_PWR_STATUS),
				DCFEV_MEM_PWR_STATUS,
				SCLV_COEFF_MEM_PWR_STATE) == 0)
			break;

		udelay(1);
	}

	set_reg_field_value(select, filter_type, SCLV_COEF_RAM_SELECT, SCL_C_RAM_FILTER_TYPE);

	for (phase = 0; phase < phases_to_program; phase++) {
		/*we always program N/2 + 1 phases, total phases N, but N/2-1 are just mirror
		phase 0 is unique and phase N/2 is unique if N is even*/
		set_reg_field_value(select, phase, SCLV_COEF_RAM_SELECT, SCL_C_RAM_PHASE);
		for (pair = 0; pair < taps_pairs; pair++) {
			uint32_t data = 0;

			set_reg_field_value(select, pair,
					SCLV_COEF_RAM_SELECT, SCL_C_RAM_TAP_PAIR_IDX);

			dm_write_reg(ctx, mmSCLV_COEF_RAM_SELECT, select);

			set_reg_field_value(
					data, 1,
					SCLV_COEF_RAM_TAP_DATA,
					SCL_C_RAM_EVEN_TAP_COEF_EN);
			set_reg_field_value(
					data, coeffs[array_idx],
					SCLV_COEF_RAM_TAP_DATA,
					SCL_C_RAM_EVEN_TAP_COEF);

			if (taps % 2 && pair == taps_pairs - 1) {
				set_reg_field_value(
						data, 0,
						SCLV_COEF_RAM_TAP_DATA,
						SCL_C_RAM_ODD_TAP_COEF_EN);
				array_idx++;
			} else {
				set_reg_field_value(
						data, 1,
						SCLV_COEF_RAM_TAP_DATA,
						SCL_C_RAM_ODD_TAP_COEF_EN);
				set_reg_field_value(
						data, coeffs[array_idx + 1],
						SCLV_COEF_RAM_TAP_DATA,
						SCL_C_RAM_ODD_TAP_COEF);

				array_idx += 2;
			}

			dm_write_reg(ctx, mmSCLV_COEF_RAM_TAP_DATA, data);
		}
	}

	/*We need to restore power gating on coeff memory to initial state*/
	dm_write_reg(ctx, mmDCFEV_MEM_PWR_CTRL, power_ctl);
}