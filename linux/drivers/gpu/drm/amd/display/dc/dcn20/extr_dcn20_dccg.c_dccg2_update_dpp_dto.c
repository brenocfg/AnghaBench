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
struct dcn_dccg {int dummy; } ;
struct dccg {int ref_dppclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPPCLK0_DTO_MODULO ; 
 int /*<<< orphan*/  DPPCLK0_DTO_PHASE ; 
 int /*<<< orphan*/  DPPCLK_DTO_CTRL ; 
 int /*<<< orphan*/ * DPPCLK_DTO_ENABLE ; 
 int /*<<< orphan*/ * DPPCLK_DTO_PARAM ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn_dccg* TO_DCN_DCCG (struct dccg*) ; 

void dccg2_update_dpp_dto(struct dccg *dccg,
		int dpp_inst,
		int req_dppclk,
		bool reduce_divider_only)
{
	struct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	if (dccg->ref_dppclk && req_dppclk) {
		int ref_dppclk = dccg->ref_dppclk;
		int current_phase, current_modulo;

		ASSERT(req_dppclk <= ref_dppclk);
		/* need to clamp to 8 bits */
		if (ref_dppclk > 0xff) {
			int divider = (ref_dppclk + 0xfe) / 0xff;

			ref_dppclk /= divider;
			req_dppclk = (req_dppclk + divider - 1) / divider;
			if (req_dppclk > ref_dppclk)
				req_dppclk = ref_dppclk;
		}

		REG_GET_2(DPPCLK_DTO_PARAM[dpp_inst],
				DPPCLK0_DTO_PHASE, &current_phase,
				DPPCLK0_DTO_MODULO, &current_modulo);

		if (reduce_divider_only) {
			// requested phase/modulo greater than current
			if (req_dppclk * current_modulo >= current_phase * ref_dppclk) {
				REG_SET_2(DPPCLK_DTO_PARAM[dpp_inst], 0,
						DPPCLK0_DTO_PHASE, req_dppclk,
						DPPCLK0_DTO_MODULO, ref_dppclk);
			} else {
				REG_SET_2(DPPCLK_DTO_PARAM[dpp_inst], 0,
						DPPCLK0_DTO_PHASE, current_phase,
						DPPCLK0_DTO_MODULO, current_modulo);
			}
		} else {
			REG_SET_2(DPPCLK_DTO_PARAM[dpp_inst], 0,
					DPPCLK0_DTO_PHASE, req_dppclk,
					DPPCLK0_DTO_MODULO, ref_dppclk);
		}

		REG_UPDATE(DPPCLK_DTO_CTRL,
				DPPCLK_DTO_ENABLE[dpp_inst], 1);
	} else {
		REG_UPDATE(DPPCLK_DTO_CTRL,
				DPPCLK_DTO_ENABLE[dpp_inst], 0);
	}
}