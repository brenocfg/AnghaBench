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
struct stv090x_state {int srate; int algo; int search_range; scalar_t__ search_mode; TYPE_1__* internal; } ;
typedef  int s16 ;
struct TYPE_2__ {int dev_ver; int mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARCFG ; 
 int /*<<< orphan*/  CARFREQ ; 
 int /*<<< orphan*/  CARHDR ; 
 int /*<<< orphan*/  CFRINIT0 ; 
 int /*<<< orphan*/  CFRINIT1 ; 
 int /*<<< orphan*/  CFRLOW0 ; 
 int /*<<< orphan*/  CFRLOW1 ; 
 int /*<<< orphan*/  CFRUP0 ; 
 int /*<<< orphan*/  CFRUP1 ; 
 int /*<<< orphan*/  CFR_AUTOSCAN_FIELD ; 
 int /*<<< orphan*/  DMDCFG2 ; 
 int /*<<< orphan*/  DMDCFGMD ; 
 int /*<<< orphan*/  DMDISTATE ; 
 int /*<<< orphan*/  EQUALCFG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  FFECFG ; 
 int /*<<< orphan*/  I2C_DEMOD_MODE_FIELD ; 
 int LSB (int) ; 
 int MSB (int) ; 
 int /*<<< orphan*/  RTC ; 
 int /*<<< orphan*/  RTCS2 ; 
 int /*<<< orphan*/  S1S2_SEQUENTIAL_FIELD ; 
 int /*<<< orphan*/  SCAN_ENABLE_FIELD ; 
 int /*<<< orphan*/  SFRSTEP ; 
#define  STV090x_COLD_SEARCH 129 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ STV090x_SEARCH_AUTO ; 
 scalar_t__ STV090x_SEARCH_DSS ; 
 scalar_t__ STV090x_SEARCH_DVBS1 ; 
 int /*<<< orphan*/  STV090x_SETFIELD_Px (int,int /*<<< orphan*/ ,int) ; 
#define  STV090x_WARM_SEARCH 128 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TMGTHFALL ; 
 int /*<<< orphan*/  TMGTHRISE ; 
 int /*<<< orphan*/  VAVSRVIT ; 
 int /*<<< orphan*/  VITSCALE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int stv090x_start_search(struct stv090x_state *state)
{
	u32 reg, freq_abs;
	s16 freq;

	/* Reset demodulator */
	reg = STV090x_READ_DEMOD(state, DMDISTATE);
	STV090x_SETFIELD_Px(reg, I2C_DEMOD_MODE_FIELD, 0x1f);
	if (STV090x_WRITE_DEMOD(state, DMDISTATE, reg) < 0)
		goto err;

	if (state->internal->dev_ver <= 0x20) {
		if (state->srate <= 5000000) {
			if (STV090x_WRITE_DEMOD(state, CARCFG, 0x44) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, CFRUP1, 0x0f) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, CFRUP0, 0xff) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, CFRLOW1, 0xf0) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, CFRLOW0, 0x00) < 0)
				goto err;

			/*enlarge the timing bandwidth for Low SR*/
			if (STV090x_WRITE_DEMOD(state, RTCS2, 0x68) < 0)
				goto err;
		} else {
			/* If the symbol rate is >5 Msps
			Set The carrier search up and low to auto mode */
			if (STV090x_WRITE_DEMOD(state, CARCFG, 0xc4) < 0)
				goto err;
			/*reduce the timing bandwidth for high SR*/
			if (STV090x_WRITE_DEMOD(state, RTCS2, 0x44) < 0)
				goto err;
		}
	} else {
		/* >= Cut 3 */
		if (state->srate <= 5000000) {
			/* enlarge the timing bandwidth for Low SR */
			STV090x_WRITE_DEMOD(state, RTCS2, 0x68);
		} else {
			/* reduce timing bandwidth for high SR */
			STV090x_WRITE_DEMOD(state, RTCS2, 0x44);
		}

		/* Set CFR min and max to manual mode */
		STV090x_WRITE_DEMOD(state, CARCFG, 0x46);

		if (state->algo == STV090x_WARM_SEARCH) {
			/* WARM Start
			 * CFR min = -1MHz,
			 * CFR max = +1MHz
			 */
			freq_abs  = 1000 << 16;
			freq_abs /= (state->internal->mclk / 1000);
			freq      = (s16) freq_abs;
		} else {
			/* COLD Start
			 * CFR min =- (SearchRange / 2 + 600KHz)
			 * CFR max = +(SearchRange / 2 + 600KHz)
			 * (600KHz for the tuner step size)
			 */
			freq_abs  = (state->search_range / 2000) + 600;
			freq_abs  = freq_abs << 16;
			freq_abs /= (state->internal->mclk / 1000);
			freq      = (s16) freq_abs;
		}

		if (STV090x_WRITE_DEMOD(state, CFRUP1, MSB(freq)) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, CFRUP0, LSB(freq)) < 0)
			goto err;

		freq *= -1;

		if (STV090x_WRITE_DEMOD(state, CFRLOW1, MSB(freq)) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, CFRLOW0, LSB(freq)) < 0)
			goto err;

	}

	if (STV090x_WRITE_DEMOD(state, CFRINIT1, 0) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, CFRINIT0, 0) < 0)
		goto err;

	if (state->internal->dev_ver >= 0x20) {
		if (STV090x_WRITE_DEMOD(state, EQUALCFG, 0x41) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, FFECFG, 0x41) < 0)
			goto err;

		if ((state->search_mode == STV090x_SEARCH_DVBS1)	||
			(state->search_mode == STV090x_SEARCH_DSS)	||
			(state->search_mode == STV090x_SEARCH_AUTO)) {

			if (STV090x_WRITE_DEMOD(state, VITSCALE, 0x82) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, VAVSRVIT, 0x00) < 0)
				goto err;
		}
	}

	if (STV090x_WRITE_DEMOD(state, SFRSTEP, 0x00) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, TMGTHRISE, 0xe0) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, TMGTHFALL, 0xc0) < 0)
		goto err;

	reg = STV090x_READ_DEMOD(state, DMDCFGMD);
	STV090x_SETFIELD_Px(reg, SCAN_ENABLE_FIELD, 0);
	STV090x_SETFIELD_Px(reg, CFR_AUTOSCAN_FIELD, 0);
	if (STV090x_WRITE_DEMOD(state, DMDCFGMD, reg) < 0)
		goto err;
	reg = STV090x_READ_DEMOD(state, DMDCFG2);
	STV090x_SETFIELD_Px(reg, S1S2_SEQUENTIAL_FIELD, 0x0);
	if (STV090x_WRITE_DEMOD(state, DMDCFG2, reg) < 0)
		goto err;

	if (STV090x_WRITE_DEMOD(state, RTC, 0x88) < 0)
		goto err;

	if (state->internal->dev_ver >= 0x20) {
		/*Frequency offset detector setting*/
		if (state->srate < 2000000) {
			if (state->internal->dev_ver <= 0x20) {
				/* Cut 2 */
				if (STV090x_WRITE_DEMOD(state, CARFREQ, 0x39) < 0)
					goto err;
			} else {
				/* Cut 3 */
				if (STV090x_WRITE_DEMOD(state, CARFREQ, 0x89) < 0)
					goto err;
			}
			if (STV090x_WRITE_DEMOD(state, CARHDR, 0x40) < 0)
				goto err;
		} else if (state->srate < 10000000) {
			if (STV090x_WRITE_DEMOD(state, CARFREQ, 0x4c) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, CARHDR, 0x20) < 0)
				goto err;
		} else {
			if (STV090x_WRITE_DEMOD(state, CARFREQ, 0x4b) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, CARHDR, 0x20) < 0)
				goto err;
		}
	} else {
		if (state->srate < 10000000) {
			if (STV090x_WRITE_DEMOD(state, CARFREQ, 0xef) < 0)
				goto err;
		} else {
			if (STV090x_WRITE_DEMOD(state, CARFREQ, 0xed) < 0)
				goto err;
		}
	}

	switch (state->algo) {
	case STV090x_WARM_SEARCH:
		/* The symbol rate and the exact
		 * carrier Frequency are known
		 */
		if (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1f) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x18) < 0)
			goto err;
		break;

	case STV090x_COLD_SEARCH:
		/* The symbol rate is known */
		if (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x1f) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, DMDISTATE, 0x15) < 0)
			goto err;
		break;

	default:
		break;
	}
	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}