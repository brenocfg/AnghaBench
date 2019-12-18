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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct mpc {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  ctx; } ;
struct dcn20_mpc {TYPE_5__ base; TYPE_4__* mpc_mask; TYPE_2__* mpc_shift; } ;
struct TYPE_8__ {int /*<<< orphan*/  csc_c12; int /*<<< orphan*/  csc_c11; } ;
struct TYPE_6__ {int /*<<< orphan*/  csc_c12; int /*<<< orphan*/  csc_c11; } ;
struct color_matrices_reg {void* csc_c33_c34; void* csc_c11_c12; TYPE_3__ masks; TYPE_1__ shifts; } ;
typedef  enum mpc_output_csc_mode { ____Placeholder_mpc_output_csc_mode } mpc_output_csc_mode ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
struct TYPE_9__ {int /*<<< orphan*/  MPC_OCSC_C12_A; int /*<<< orphan*/  MPC_OCSC_C11_A; } ;
struct TYPE_7__ {int /*<<< orphan*/  MPC_OCSC_C12_A; int /*<<< orphan*/  MPC_OCSC_C11_A; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/ * CSC_C11_C12_A ; 
 int /*<<< orphan*/ * CSC_C11_C12_B ; 
 int /*<<< orphan*/ * CSC_C33_C34_A ; 
 int /*<<< orphan*/ * CSC_C33_C34_B ; 
 int /*<<< orphan*/ * CSC_MODE ; 
 int /*<<< orphan*/  MPC_OCSC_MODE ; 
 int MPC_OUTPUT_CSC_COEF_A ; 
 int MPC_OUTPUT_CSC_DISABLE ; 
 void* REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_mpc* TO_DCN20_MPC (struct mpc*) ; 
 int /*<<< orphan*/  cm_helper_program_color_matrices (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct color_matrices_reg*) ; 
 int /*<<< orphan*/ * find_color_matrix (int,int /*<<< orphan*/ *) ; 

void mpc2_set_ocsc_default(
		struct mpc *mpc,
		int opp_id,
		enum dc_color_space color_space,
		enum mpc_output_csc_mode ocsc_mode)
{
	struct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	uint32_t arr_size;
	struct color_matrices_reg ocsc_regs;
	const uint16_t *regval = NULL;

	REG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
	if (ocsc_mode == MPC_OUTPUT_CSC_DISABLE)
		return;

	regval = find_color_matrix(color_space, &arr_size);

	if (regval == NULL) {
		BREAK_TO_DEBUGGER();
		return;
	}

	ocsc_regs.shifts.csc_c11 = mpc20->mpc_shift->MPC_OCSC_C11_A;
	ocsc_regs.masks.csc_c11  = mpc20->mpc_mask->MPC_OCSC_C11_A;
	ocsc_regs.shifts.csc_c12 = mpc20->mpc_shift->MPC_OCSC_C12_A;
	ocsc_regs.masks.csc_c12 = mpc20->mpc_mask->MPC_OCSC_C12_A;


	if (ocsc_mode == MPC_OUTPUT_CSC_COEF_A) {
		ocsc_regs.csc_c11_c12 = REG(CSC_C11_C12_A[opp_id]);
		ocsc_regs.csc_c33_c34 = REG(CSC_C33_C34_A[opp_id]);
	} else {
		ocsc_regs.csc_c11_c12 = REG(CSC_C11_C12_B[opp_id]);
		ocsc_regs.csc_c33_c34 = REG(CSC_C33_C34_B[opp_id]);
	}

	cm_helper_program_color_matrices(
			mpc20->base.ctx,
			regval,
			&ocsc_regs);
}