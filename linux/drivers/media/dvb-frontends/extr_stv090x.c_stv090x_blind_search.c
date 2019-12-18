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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct stv090x_state {int /*<<< orphan*/  DemodTimeout; TYPE_1__* internal; } ;
typedef  int s32 ;
struct TYPE_2__ {int dev_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC2I0 ; 
 int /*<<< orphan*/  AGC2I1 ; 
 int /*<<< orphan*/  CARCFG ; 
 int /*<<< orphan*/  CFR_OVERFLOW_FIELD ; 
 int /*<<< orphan*/  DEMOD_DELOCK_FIELD ; 
 int /*<<< orphan*/  DSTATUS2 ; 
 int /*<<< orphan*/  EQUALCFG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  FFECFG ; 
 int /*<<< orphan*/  KREFTMG ; 
 int /*<<< orphan*/  RTCS2 ; 
 int STV090x_GETFIELD_Px (scalar_t__,int /*<<< orphan*/ ) ; 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ STV090x_SEARCH_AGC2_TH (int) ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VAVSRVIT ; 
 int /*<<< orphan*/  VITSCALE ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ stv090x_get_agc2_min_level (struct stv090x_state*) ; 
 int stv090x_get_dmdlock (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv090x_get_lock_tmg (struct stv090x_state*) ; 
 scalar_t__ stv090x_srate_srch_coarse (struct stv090x_state*) ; 
 scalar_t__ stv090x_srate_srch_fine (struct stv090x_state*) ; 

__attribute__((used)) static int stv090x_blind_search(struct stv090x_state *state)
{
	u32 agc2, reg, srate_coarse;
	s32 cpt_fail, agc2_ovflw, i;
	u8 k_ref, k_max, k_min;
	int coarse_fail = 0;
	int lock;

	k_max = 110;
	k_min = 10;

	agc2 = stv090x_get_agc2_min_level(state);

	if (agc2 > STV090x_SEARCH_AGC2_TH(state->internal->dev_ver)) {
		lock = 0;
	} else {

		if (state->internal->dev_ver <= 0x20) {
			if (STV090x_WRITE_DEMOD(state, CARCFG, 0xc4) < 0)
				goto err;
		} else {
			/* > Cut 3 */
			if (STV090x_WRITE_DEMOD(state, CARCFG, 0x06) < 0)
				goto err;
		}

		if (STV090x_WRITE_DEMOD(state, RTCS2, 0x44) < 0)
			goto err;

		if (state->internal->dev_ver >= 0x20) {
			if (STV090x_WRITE_DEMOD(state, EQUALCFG, 0x41) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, FFECFG, 0x41) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, VITSCALE, 0x82) < 0)
				goto err;
			if (STV090x_WRITE_DEMOD(state, VAVSRVIT, 0x00) < 0) /* set viterbi hysteresis */
				goto err;
		}

		k_ref = k_max;
		do {
			if (STV090x_WRITE_DEMOD(state, KREFTMG, k_ref) < 0)
				goto err;
			if (stv090x_srate_srch_coarse(state) != 0) {
				srate_coarse = stv090x_srate_srch_fine(state);
				if (srate_coarse != 0) {
					stv090x_get_lock_tmg(state);
					lock = stv090x_get_dmdlock(state,
							state->DemodTimeout);
				} else {
					lock = 0;
				}
			} else {
				cpt_fail = 0;
				agc2_ovflw = 0;
				for (i = 0; i < 10; i++) {
					agc2 += (STV090x_READ_DEMOD(state, AGC2I1) << 8) |
						STV090x_READ_DEMOD(state, AGC2I0);
					if (agc2 >= 0xff00)
						agc2_ovflw++;
					reg = STV090x_READ_DEMOD(state, DSTATUS2);
					if ((STV090x_GETFIELD_Px(reg, CFR_OVERFLOW_FIELD) == 0x01) &&
					    (STV090x_GETFIELD_Px(reg, DEMOD_DELOCK_FIELD) == 0x01))

						cpt_fail++;
				}
				if ((cpt_fail > 7) || (agc2_ovflw > 7))
					coarse_fail = 1;

				lock = 0;
			}
			k_ref -= 20;
		} while ((k_ref >= k_min) && (!lock) && (!coarse_fail));
	}

	return lock;

err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}