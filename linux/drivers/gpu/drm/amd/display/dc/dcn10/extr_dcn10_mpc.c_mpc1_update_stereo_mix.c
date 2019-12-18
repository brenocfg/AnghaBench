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
struct mpcc_sm_cfg {int /*<<< orphan*/  force_next_field_polarity; int /*<<< orphan*/  force_next_frame_porlarity; int /*<<< orphan*/  field_alt; int /*<<< orphan*/  frame_alt; int /*<<< orphan*/  sm_mode; int /*<<< orphan*/  enable; } ;
struct mpc {int dummy; } ;
struct dcn10_mpc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MPCC_SM_CONTROL ; 
 int /*<<< orphan*/  MPCC_SM_EN ; 
 int /*<<< orphan*/  MPCC_SM_FIELD_ALT ; 
 int /*<<< orphan*/  MPCC_SM_FORCE_NEXT_FRAME_POL ; 
 int /*<<< orphan*/  MPCC_SM_FORCE_NEXT_TOP_POL ; 
 int /*<<< orphan*/  MPCC_SM_FRAME_ALT ; 
 int /*<<< orphan*/  MPCC_SM_MODE ; 
 int /*<<< orphan*/  REG_UPDATE_6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_mpc* TO_DCN10_MPC (struct mpc*) ; 

void mpc1_update_stereo_mix(
	struct mpc *mpc,
	struct mpcc_sm_cfg *sm_cfg,
	int mpcc_id)
{
	struct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	REG_UPDATE_6(MPCC_SM_CONTROL[mpcc_id],
			MPCC_SM_EN,			sm_cfg->enable,
			MPCC_SM_MODE,			sm_cfg->sm_mode,
			MPCC_SM_FRAME_ALT,		sm_cfg->frame_alt,
			MPCC_SM_FIELD_ALT,		sm_cfg->field_alt,
			MPCC_SM_FORCE_NEXT_FRAME_POL,	sm_cfg->force_next_frame_porlarity,
			MPCC_SM_FORCE_NEXT_TOP_POL,	sm_cfg->force_next_field_polarity);
}