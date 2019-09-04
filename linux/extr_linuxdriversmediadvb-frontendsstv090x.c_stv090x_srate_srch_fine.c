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
struct stv090x_state {int srate; TYPE_1__* internal; } ;
struct TYPE_2__ {int mclk; int dev_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC2REF ; 
 int /*<<< orphan*/  CARFREQ ; 
 int /*<<< orphan*/  CFR1 ; 
 int /*<<< orphan*/  CFR2 ; 
 int /*<<< orphan*/  CFRINIT0 ; 
 int /*<<< orphan*/  CFRINIT1 ; 
 int /*<<< orphan*/  CFR_AUTOSCAN_FIELD ; 
 int /*<<< orphan*/  DMDCFGMD ; 
 int /*<<< orphan*/  DMDISTATE ; 
 int /*<<< orphan*/  DMDTOM ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  SFRINIT0 ; 
 int /*<<< orphan*/  SFRINIT1 ; 
 int /*<<< orphan*/  SFRLOW0 ; 
 int /*<<< orphan*/  SFRLOW1 ; 
 int /*<<< orphan*/  SFRUP0 ; 
 int /*<<< orphan*/  SFRUP1 ; 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_SETFIELD_Px (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TMGCFG ; 
 int /*<<< orphan*/  TMGCFG2 ; 
 int /*<<< orphan*/  TMGTHFALL ; 
 int /*<<< orphan*/  TMGTHRISE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int stv090x_get_srate (struct stv090x_state*,int) ; 

__attribute__((used)) static u32 stv090x_srate_srch_fine(struct stv090x_state *state)
{
	u32 srate_coarse, freq_coarse, sym, reg;

	srate_coarse = stv090x_get_srate(state, state->internal->mclk);
	freq_coarse  = STV090x_READ_DEMOD(state, CFR2) << 8;
	freq_coarse |= STV090x_READ_DEMOD(state, CFR1);
	sym = 13 * (srate_coarse / 10); /* SFRUP = SFR + 30% */

	if (sym < state->srate)
		srate_coarse = 0;
	else {
		if (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1f) < 0) /* Demod RESET */
			goto err;
		if (STV090x_WRITE_DEMOD(state, TMGCFG2, 0xc1) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, TMGTHRISE, 0x20) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, TMGTHFALL, 0x00) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, TMGCFG, 0xd2) < 0)
			goto err;
		reg = STV090x_READ_DEMOD(state, DMDCFGMD);
		STV090x_SETFIELD_Px(reg, CFR_AUTOSCAN_FIELD, 0x00);
		if (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
			goto err;

		if (STV090x_WRITE_DEMOD(state, AGC2REF, 0x38) < 0)
			goto err;

		if (state->internal->dev_ver >= 0x30) {
			if (STV090x_WRITE_DEMOD(state, CARFREQ, 0x79) < 0)
				goto err;
		} else if (state->internal->dev_ver >= 0x20) {
			if (STV090x_WRITE_DEMOD(state, CARFREQ, 0x49) < 0)
				goto err;
		}

		if (srate_coarse > 3000000) {
			sym  = 13 * (srate_coarse / 10); /* SFRUP = SFR + 30% */
			sym  = (sym / 1000) * 65536;
			sym /= (state->internal->mclk / 1000);
			if (STV090x_WRITE_DEMOD(state, SFRUP1, (sym >> 8) & 0x7f) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, SFRUP0, sym & 0xff) < 0)
				goto err;
			sym  = 10 * (srate_coarse / 13); /* SFRLOW = SFR - 30% */
			sym  = (sym / 1000) * 65536;
			sym /= (state->internal->mclk / 1000);
			if (STV090x_WRITE_DEMOD(state, SFRLOW1, (sym >> 8) & 0x7f) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, SFRLOW0, sym & 0xff) < 0)
				goto err;
			sym  = (srate_coarse / 1000) * 65536;
			sym /= (state->internal->mclk / 1000);
			if (STV090x_WRITE_DEMOD(state, SFRINIT1, (sym >> 8) & 0xff) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, SFRINIT0, sym & 0xff) < 0)
				goto err;
		} else {
			sym  = 13 * (srate_coarse / 10); /* SFRUP = SFR + 30% */
			sym  = (sym / 100) * 65536;
			sym /= (state->internal->mclk / 100);
			if (STV090x_WRITE_DEMOD(state, SFRUP1, (sym >> 8) & 0x7f) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, SFRUP0, sym & 0xff) < 0)
				goto err;
			sym  = 10 * (srate_coarse / 14); /* SFRLOW = SFR - 30% */
			sym  = (sym / 100) * 65536;
			sym /= (state->internal->mclk / 100);
			if (STV090x_WRITE_DEMOD(state, SFRLOW1, (sym >> 8) & 0x7f) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, SFRLOW0, sym & 0xff) < 0)
				goto err;
			sym  = (srate_coarse / 100) * 65536;
			sym /= (state->internal->mclk / 100);
			if (STV090x_WRITE_DEMOD(state, SFRINIT1, (sym >> 8) & 0xff) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, SFRINIT0, sym & 0xff) < 0)
				goto err;
		}
		if (STV090x_WRITE_DEMOD(state, DMDTOM, 0x20) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, CFRINIT1, (freq_coarse >> 8) & 0xff) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, CFRINIT0, freq_coarse & 0xff) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x15) < 0) /* trigger acquisition */
			goto err;
	}

	return srate_coarse;

err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}