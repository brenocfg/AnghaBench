#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/  ctx; } ;
struct dcn10_dpp {TYPE_5__ base; TYPE_4__* tf_mask; TYPE_2__* tf_shift; } ;
struct TYPE_8__ {int /*<<< orphan*/  csc_c12; int /*<<< orphan*/  csc_c11; } ;
struct TYPE_6__ {int /*<<< orphan*/  csc_c12; int /*<<< orphan*/  csc_c11; } ;
struct color_matrices_reg {void* csc_c33_c34; void* csc_c11_c12; TYPE_3__ masks; TYPE_1__ shifts; } ;
struct TYPE_9__ {int /*<<< orphan*/  CM_OCSC_C12; int /*<<< orphan*/  CM_OCSC_C11; } ;
struct TYPE_7__ {int /*<<< orphan*/  CM_OCSC_C12; int /*<<< orphan*/  CM_OCSC_C11; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  CM_COMB_C11_C12 ; 
 int /*<<< orphan*/  CM_COMB_C33_C34 ; 
 int /*<<< orphan*/  CM_OCSC_C11_C12 ; 
 int /*<<< orphan*/  CM_OCSC_C33_C34 ; 
 int /*<<< orphan*/  CM_OCSC_CONTROL ; 
 int /*<<< orphan*/  CM_OCSC_MODE ; 
 int /*<<< orphan*/  CM_TEST_DEBUG_DATA ; 
 int /*<<< orphan*/  CM_TEST_DEBUG_DATA_ID9_OCSC_MODE ; 
 int /*<<< orphan*/  CM_TEST_DEBUG_INDEX ; 
 void* REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cm_helper_program_color_matrices (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct color_matrices_reg*) ; 

__attribute__((used)) static void dpp1_cm_program_color_matrix(
		struct dcn10_dpp *dpp,
		const uint16_t *regval)
{
	uint32_t ocsc_mode;
	uint32_t cur_mode;
	struct color_matrices_reg gam_regs;

	if (regval == NULL) {
		BREAK_TO_DEBUGGER();
		return;
	}

	/* determine which CSC matrix (ocsc or comb) we are using
	 * currently.  select the alternate set to double buffer
	 * the CSC update so CSC is updated on frame boundary
	 */
	REG_SET(CM_TEST_DEBUG_INDEX, 0,
			CM_TEST_DEBUG_INDEX, 9);

	REG_GET(CM_TEST_DEBUG_DATA,
			CM_TEST_DEBUG_DATA_ID9_OCSC_MODE, &cur_mode);

	if (cur_mode != 4)
		ocsc_mode = 4;
	else
		ocsc_mode = 5;


	gam_regs.shifts.csc_c11 = dpp->tf_shift->CM_OCSC_C11;
	gam_regs.masks.csc_c11  = dpp->tf_mask->CM_OCSC_C11;
	gam_regs.shifts.csc_c12 = dpp->tf_shift->CM_OCSC_C12;
	gam_regs.masks.csc_c12 = dpp->tf_mask->CM_OCSC_C12;

	if (ocsc_mode == 4) {

		gam_regs.csc_c11_c12 = REG(CM_OCSC_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_OCSC_C33_C34);

	} else {

		gam_regs.csc_c11_c12 = REG(CM_COMB_C11_C12);
		gam_regs.csc_c33_c34 = REG(CM_COMB_C33_C34);

	}

	cm_helper_program_color_matrices(
			dpp->base.ctx,
			regval,
			&gam_regs);

	REG_SET(CM_OCSC_CONTROL, 0, CM_OCSC_MODE, ocsc_mode);

}