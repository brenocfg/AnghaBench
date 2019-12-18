#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mpc {TYPE_4__* ctx; } ;
struct dcn20_mpc {int dummy; } ;
typedef  enum dc_lut_mode { ____Placeholder_dc_lut_mode } dc_lut_mode ;
struct TYPE_8__ {TYPE_2__* dc; } ;
struct TYPE_7__ {int dedcn20_305_wa; } ;
struct TYPE_5__ {scalar_t__ cm_in_bypass; } ;
struct TYPE_6__ {TYPE_3__ work_arounds; TYPE_1__ debug; } ;

/* Variables and functions */
 int LUT_BYPASS ; 
 int LUT_RAM_A ; 
 int /*<<< orphan*/ * MPCC_OGAM_MODE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct dcn20_mpc* TO_DCN20_MPC (struct mpc*) ; 

void apply_DEDCN20_305_wa(
		struct mpc *mpc,
		int mpcc_id, enum dc_lut_mode current_mode,
		enum dc_lut_mode next_mode)
{
	struct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	if (mpc->ctx->dc->debug.cm_in_bypass) {
		REG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		return;
	}

	if (mpc->ctx->dc->work_arounds.dedcn20_305_wa == false) {
		/*hw fixed in new review*/
		return;
	}
	if (current_mode == LUT_BYPASS)
		/*this will only work if OTG is locked.
		 *if we were to support OTG unlock case,
		 *the workaround will be more complex
		 */
		REG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE,
			next_mode == LUT_RAM_A ? 1:2);
}