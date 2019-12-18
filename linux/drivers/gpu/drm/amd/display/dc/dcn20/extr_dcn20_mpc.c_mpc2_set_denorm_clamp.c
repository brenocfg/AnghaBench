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
struct mpc_denorm_clamp {int /*<<< orphan*/  clamp_min_b_cb; int /*<<< orphan*/  clamp_max_b_cb; int /*<<< orphan*/  clamp_min_g_y; int /*<<< orphan*/  clamp_max_g_y; int /*<<< orphan*/  clamp_min_r_cr; int /*<<< orphan*/  clamp_max_r_cr; } ;
struct mpc {int dummy; } ;
struct dcn20_mpc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DENORM_CLAMP_B_CB ; 
 int /*<<< orphan*/ * DENORM_CLAMP_G_Y ; 
 int /*<<< orphan*/ * DENORM_CONTROL ; 
 int /*<<< orphan*/  MPC_OUT_DENORM_CLAMP_MAX_B_CB ; 
 int /*<<< orphan*/  MPC_OUT_DENORM_CLAMP_MAX_G_Y ; 
 int /*<<< orphan*/  MPC_OUT_DENORM_CLAMP_MAX_R_CR ; 
 int /*<<< orphan*/  MPC_OUT_DENORM_CLAMP_MIN_B_CB ; 
 int /*<<< orphan*/  MPC_OUT_DENORM_CLAMP_MIN_G_Y ; 
 int /*<<< orphan*/  MPC_OUT_DENORM_CLAMP_MIN_R_CR ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn20_mpc* TO_DCN20_MPC (struct mpc*) ; 

void mpc2_set_denorm_clamp(
		struct mpc *mpc,
		int opp_id,
		struct mpc_denorm_clamp denorm_clamp)
{
	struct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	REG_UPDATE_2(DENORM_CONTROL[opp_id],
			MPC_OUT_DENORM_CLAMP_MAX_R_CR, denorm_clamp.clamp_max_r_cr,
			MPC_OUT_DENORM_CLAMP_MIN_R_CR, denorm_clamp.clamp_min_r_cr);
	REG_UPDATE_2(DENORM_CLAMP_G_Y[opp_id],
			MPC_OUT_DENORM_CLAMP_MAX_G_Y, denorm_clamp.clamp_max_g_y,
			MPC_OUT_DENORM_CLAMP_MIN_G_Y, denorm_clamp.clamp_min_g_y);
	REG_UPDATE_2(DENORM_CLAMP_B_CB[opp_id],
			MPC_OUT_DENORM_CLAMP_MAX_B_CB, denorm_clamp.clamp_max_b_cb,
			MPC_OUT_DENORM_CLAMP_MIN_B_CB, denorm_clamp.clamp_min_b_cb);
}