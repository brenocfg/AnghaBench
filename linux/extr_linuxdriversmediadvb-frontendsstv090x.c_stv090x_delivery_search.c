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
typedef  int u32 ;
struct stv090x_state {int search_mode; int /*<<< orphan*/  demod_mode; TYPE_1__* internal; } ;
struct TYPE_2__ {int dev_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLC ; 
 int /*<<< orphan*/  BCLC ; 
 int /*<<< orphan*/  CAR2CFG ; 
 int /*<<< orphan*/  DMDCFGMD ; 
 int /*<<< orphan*/  DVBS1_ENABLE_FIELD ; 
 int /*<<< orphan*/  DVBS2_ENABLE_FIELD ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
#define  STV090x_SEARCH_AUTO 131 
#define  STV090x_SEARCH_DSS 130 
#define  STV090x_SEARCH_DVBS1 129 
#define  STV090x_SEARCH_DVBS2 128 
 int /*<<< orphan*/  STV090x_SETFIELD_Px (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STV090x_SINGLE ; 
 int /*<<< orphan*/  STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  stv090x_activate_modcod (struct stv090x_state*) ; 
 int /*<<< orphan*/  stv090x_activate_modcod_single (struct stv090x_state*) ; 
 int /*<<< orphan*/  stv090x_dvbs_track_crl (struct stv090x_state*) ; 
 int /*<<< orphan*/  stv090x_set_vit_thacq (struct stv090x_state*) ; 
 int /*<<< orphan*/  stv090x_set_vit_thtracq (struct stv090x_state*) ; 
 int /*<<< orphan*/  stv090x_set_viterbi (struct stv090x_state*) ; 
 int /*<<< orphan*/  stv090x_vitclk_ctl (struct stv090x_state*,int) ; 

__attribute__((used)) static int stv090x_delivery_search(struct stv090x_state *state)
{
	u32 reg;

	switch (state->search_mode) {
	case STV090x_SEARCH_DVBS1:
	case STV090x_SEARCH_DSS:
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 1);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 0);
		if (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			goto err;

		/* Activate Viterbi decoder in legacy search,
		 * do not use FRESVIT1, might impact VITERBI2
		 */
		if (stv090x_vitclk_ctl(state, 0) < 0)
			goto err;

		if (stv090x_dvbs_track_crl(state) < 0)
			goto err;

		if (STV090x_WRITE_DEMOD(state, CAR2CFG, 0x22) < 0) /* disable DVB-S2 */
			goto err;

		if (stv090x_set_vit_thacq(state) < 0)
			goto err;
		if (stv090x_set_viterbi(state) < 0)
			goto err;
		break;

	case STV090x_SEARCH_DVBS2:
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 0);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 0);
		if (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			goto err;
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 1);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 1);
		if (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			goto err;

		if (stv090x_vitclk_ctl(state, 1) < 0)
			goto err;

		if (STV090x_WRITE_DEMOD(state, ACLC, 0x1a) < 0) /* stop DVB-S CR loop */
			goto err;
		if (STV090x_WRITE_DEMOD(state, BCLC, 0x09) < 0)
			goto err;

		if (state->internal->dev_ver <= 0x20) {
			/* enable S2 carrier loop */
			if (STV090x_WRITE_DEMOD(state, CAR2CFG, 0x26) < 0)
				goto err;
		} else {
			/* > Cut 3: Stop carrier 3 */
			if (STV090x_WRITE_DEMOD(state, CAR2CFG, 0x66) < 0)
				goto err;
		}

		if (state->demod_mode != STV090x_SINGLE) {
			/* Cut 2: enable link during search */
			if (stv090x_activate_modcod(state) < 0)
				goto err;
		} else {
			/* Single demodulator
			 * Authorize SHORT and LONG frames,
			 * QPSK, 8PSK, 16APSK and 32APSK
			 */
			if (stv090x_activate_modcod_single(state) < 0)
				goto err;
		}

		if (stv090x_set_vit_thtracq(state) < 0)
			goto err;
		break;

	case STV090x_SEARCH_AUTO:
	default:
		/* enable DVB-S2 and DVB-S2 in Auto MODE */
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 0);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 0);
		if (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			goto err;
		STV090x_SETFIELD_Px(reg, DVBS1_ENABLE_FIELD, 1);
		STV090x_SETFIELD_Px(reg, DVBS2_ENABLE_FIELD, 1);
		if (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			goto err;

		if (stv090x_vitclk_ctl(state, 0) < 0)
			goto err;

		if (stv090x_dvbs_track_crl(state) < 0)
			goto err;

		if (state->internal->dev_ver <= 0x20) {
			/* enable S2 carrier loop */
			if (STV090x_WRITE_DEMOD(state, CAR2CFG, 0x26) < 0)
				goto err;
		} else {
			/* > Cut 3: Stop carrier 3 */
			if (STV090x_WRITE_DEMOD(state, CAR2CFG, 0x66) < 0)
				goto err;
		}

		if (state->demod_mode != STV090x_SINGLE) {
			/* Cut 2: enable link during search */
			if (stv090x_activate_modcod(state) < 0)
				goto err;
		} else {
			/* Single demodulator
			 * Authorize SHORT and LONG frames,
			 * QPSK, 8PSK, 16APSK and 32APSK
			 */
			if (stv090x_activate_modcod_single(state) < 0)
				goto err;
		}

		if (stv090x_set_vit_thacq(state) < 0)
			goto err;

		if (stv090x_set_viterbi(state) < 0)
			goto err;
		break;
	}
	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}