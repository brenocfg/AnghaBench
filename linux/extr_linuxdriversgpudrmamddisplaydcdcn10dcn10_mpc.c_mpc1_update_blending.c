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
struct mpcc_blnd_cfg {int /*<<< orphan*/  black_color; int /*<<< orphan*/  global_gain; int /*<<< orphan*/  global_alpha; int /*<<< orphan*/  overlap_only; int /*<<< orphan*/  pre_multiplied_alpha; int /*<<< orphan*/  alpha_mode; } ;
struct mpcc {struct mpcc_blnd_cfg blnd_cfg; } ;
struct mpc {int dummy; } ;
struct dcn10_mpc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPCC_ALPHA_BLND_MODE ; 
 int /*<<< orphan*/  MPCC_ALPHA_MULTIPLIED_MODE ; 
 int /*<<< orphan*/  MPCC_BLND_ACTIVE_OVERLAP_ONLY ; 
 int /*<<< orphan*/ * MPCC_CONTROL ; 
 int /*<<< orphan*/  MPCC_GLOBAL_ALPHA ; 
 int /*<<< orphan*/  MPCC_GLOBAL_GAIN ; 
 int /*<<< orphan*/  REG_UPDATE_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_mpc* TO_DCN10_MPC (struct mpc*) ; 
 struct mpcc* mpc1_get_mpcc (struct mpc*,int) ; 
 int /*<<< orphan*/  mpc1_set_bg_color (struct mpc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mpc1_update_blending(
	struct mpc *mpc,
	struct mpcc_blnd_cfg *blnd_cfg,
	int mpcc_id)
{
	struct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	struct mpcc *mpcc = mpc1_get_mpcc(mpc, mpcc_id);

	REG_UPDATE_5(MPCC_CONTROL[mpcc_id],
			MPCC_ALPHA_BLND_MODE,		blnd_cfg->alpha_mode,
			MPCC_ALPHA_MULTIPLIED_MODE,	blnd_cfg->pre_multiplied_alpha,
			MPCC_BLND_ACTIVE_OVERLAP_ONLY,	blnd_cfg->overlap_only,
			MPCC_GLOBAL_ALPHA,		blnd_cfg->global_alpha,
			MPCC_GLOBAL_GAIN,		blnd_cfg->global_gain);

	mpc1_set_bg_color(mpc, &blnd_cfg->black_color, mpcc_id);
	mpcc->blnd_cfg = *blnd_cfg;
}