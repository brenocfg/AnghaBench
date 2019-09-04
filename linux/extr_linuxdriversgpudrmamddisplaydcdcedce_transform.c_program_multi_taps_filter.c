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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct dce_transform {int dummy; } ;
typedef  enum ram_filter_type { ____Placeholder_ram_filter_type } ram_filter_type ;

/* Variables and functions */
 int /*<<< orphan*/  DCFE_MEM_PWR_CTRL ; 
 int /*<<< orphan*/  DCFE_MEM_PWR_STATUS ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCL_COEFF_MEM_PWR_DIS ; 
 int /*<<< orphan*/  SCL_COEFF_MEM_PWR_STATE ; 
 int /*<<< orphan*/  SCL_COEF_RAM_SELECT ; 
 int /*<<< orphan*/  SCL_COEF_RAM_TAP_DATA ; 
 int /*<<< orphan*/  SCL_C_RAM_EVEN_TAP_COEF ; 
 int /*<<< orphan*/  SCL_C_RAM_EVEN_TAP_COEF_EN ; 
 int /*<<< orphan*/  SCL_C_RAM_FILTER_TYPE ; 
 int /*<<< orphan*/  SCL_C_RAM_ODD_TAP_COEF ; 
 int /*<<< orphan*/  SCL_C_RAM_ODD_TAP_COEF_EN ; 
 int /*<<< orphan*/  SCL_C_RAM_PHASE ; 
 int /*<<< orphan*/  SCL_C_RAM_TAP_PAIR_IDX ; 
 int SCL_PHASES ; 

__attribute__((used)) static void program_multi_taps_filter(
	struct dce_transform *xfm_dce,
	int taps,
	const uint16_t *coeffs,
	enum ram_filter_type filter_type)
{
	int phase, pair;
	int array_idx = 0;
	int taps_pairs = (taps + 1) / 2;
	int phases_to_program = SCL_PHASES / 2 + 1;

	uint32_t power_ctl = 0;

	if (!coeffs)
		return;

	/*We need to disable power gating on coeff memory to do programming*/
	if (REG(DCFE_MEM_PWR_CTRL)) {
		power_ctl = REG_READ(DCFE_MEM_PWR_CTRL);
		REG_SET(DCFE_MEM_PWR_CTRL, power_ctl, SCL_COEFF_MEM_PWR_DIS, 1);

		REG_WAIT(DCFE_MEM_PWR_STATUS, SCL_COEFF_MEM_PWR_STATE, 0, 1, 10);
	}
	for (phase = 0; phase < phases_to_program; phase++) {
		/*we always program N/2 + 1 phases, total phases N, but N/2-1 are just mirror
		phase 0 is unique and phase N/2 is unique if N is even*/
		for (pair = 0; pair < taps_pairs; pair++) {
			uint16_t odd_coeff = 0;
			uint16_t even_coeff = coeffs[array_idx];

			REG_SET_3(SCL_COEF_RAM_SELECT, 0,
					SCL_C_RAM_FILTER_TYPE, filter_type,
					SCL_C_RAM_PHASE, phase,
					SCL_C_RAM_TAP_PAIR_IDX, pair);

			if (taps % 2 && pair == taps_pairs - 1)
				array_idx++;
			else {
				odd_coeff = coeffs[array_idx + 1];
				array_idx += 2;
			}

			REG_SET_4(SCL_COEF_RAM_TAP_DATA, 0,
					SCL_C_RAM_EVEN_TAP_COEF_EN, 1,
					SCL_C_RAM_EVEN_TAP_COEF, even_coeff,
					SCL_C_RAM_ODD_TAP_COEF_EN, 1,
					SCL_C_RAM_ODD_TAP_COEF, odd_coeff);
		}
	}

	/*We need to restore power gating on coeff memory to initial state*/
	if (REG(DCFE_MEM_PWR_CTRL))
		REG_WRITE(DCFE_MEM_PWR_CTRL, power_ctl);
}