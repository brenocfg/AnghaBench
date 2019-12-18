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
struct mpcc {int mpcc_id; int dpp_id; struct mpcc* mpcc_bot; } ;
struct mpc_tree {size_t opp_id; struct mpcc* opp_list; } ;
struct mpc {int dummy; } ;
struct dcn10_mpc {int mpcc_in_use_mask; } ;

/* Variables and functions */
 int MPCC_BLEND_MODE_TOP_LAYER_PASSTHROUGH ; 
 int /*<<< orphan*/ * MPCC_BOT_SEL ; 
 int /*<<< orphan*/ * MPCC_CONTROL ; 
 int /*<<< orphan*/  MPCC_MODE ; 
 int /*<<< orphan*/ * MPCC_OPP_ID ; 
 int /*<<< orphan*/ * MPCC_TOP_SEL ; 
 int /*<<< orphan*/  MPC_OUT_MUX ; 
 int /*<<< orphan*/ * MUX ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_mpc* TO_DCN10_MPC (struct mpc*) ; 

void mpc1_remove_mpcc(
	struct mpc *mpc,
	struct mpc_tree *tree,
	struct mpcc *mpcc_to_remove)
{
	struct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	bool found = false;
	int mpcc_id = mpcc_to_remove->mpcc_id;

	if (tree->opp_list == mpcc_to_remove) {
		found = true;
		/* remove MPCC from top of tree */
		if (mpcc_to_remove->mpcc_bot) {
			/* set the next MPCC in list to be the top MPCC */
			tree->opp_list = mpcc_to_remove->mpcc_bot;
			REG_UPDATE(MUX[tree->opp_id], MPC_OUT_MUX, tree->opp_list->mpcc_id);
		} else {
			/* there are no other MPCC is list */
			tree->opp_list = NULL;
			REG_UPDATE(MUX[tree->opp_id], MPC_OUT_MUX, 0xf);
		}
	} else {
		/* find mpcc to remove MPCC list */
		struct mpcc *temp_mpcc = tree->opp_list;

		while (temp_mpcc && temp_mpcc->mpcc_bot != mpcc_to_remove)
			temp_mpcc = temp_mpcc->mpcc_bot;

		if (temp_mpcc && temp_mpcc->mpcc_bot == mpcc_to_remove) {
			found = true;
			temp_mpcc->mpcc_bot = mpcc_to_remove->mpcc_bot;
			if (mpcc_to_remove->mpcc_bot) {
				/* remove MPCC in middle of list */
				REG_SET(MPCC_BOT_SEL[temp_mpcc->mpcc_id], 0,
						MPCC_BOT_SEL, mpcc_to_remove->mpcc_bot->mpcc_id);
			} else {
				/* remove MPCC from bottom of list */
				REG_SET(MPCC_BOT_SEL[temp_mpcc->mpcc_id], 0,
						MPCC_BOT_SEL, 0xf);
				REG_UPDATE(MPCC_CONTROL[temp_mpcc->mpcc_id],
						MPCC_MODE, MPCC_BLEND_MODE_TOP_LAYER_PASSTHROUGH);
			}
		}
	}

	if (found) {
		/* turn off MPCC mux registers */
		REG_SET(MPCC_TOP_SEL[mpcc_id], 0, MPCC_TOP_SEL, 0xf);
		REG_SET(MPCC_BOT_SEL[mpcc_id], 0, MPCC_BOT_SEL, 0xf);
		REG_SET(MPCC_OPP_ID[mpcc_id],  0, MPCC_OPP_ID,  0xf);

		/* mark this mpcc as not in use */
		mpc10->mpcc_in_use_mask &= ~(1 << mpcc_id);
		mpcc_to_remove->dpp_id = 0xf;
		mpcc_to_remove->mpcc_bot = NULL;
	} else {
		/* In case of resume from S3/S4, remove mpcc from bios left over */
		REG_SET(MPCC_TOP_SEL[mpcc_id], 0, MPCC_TOP_SEL, 0xf);
		REG_SET(MPCC_BOT_SEL[mpcc_id], 0, MPCC_BOT_SEL, 0xf);
		REG_SET(MPCC_OPP_ID[mpcc_id],  0, MPCC_OPP_ID,  0xf);
	}
}