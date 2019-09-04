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
typedef  int u32 ;
struct stv0900_state {int demod; struct stv0900_internal* internal; } ;
struct stv0900_internal {int chip_id; int* symbol_rate; int* srch_range; int* freq; int* tuner_type; int /*<<< orphan*/  mclk; int /*<<< orphan*/ * bw; } ;
struct dvb_frontend {struct stv0900_state* demodulator_priv; } ;
typedef  int s32 ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  AGC2I0 ; 
 int /*<<< orphan*/  AGC2I1 ; 
 int /*<<< orphan*/  AGC2REF ; 
 int /*<<< orphan*/  CARFREQ ; 
 int /*<<< orphan*/  CFR_AUTOSCAN ; 
 int /*<<< orphan*/  DEMOD_MODE ; 
 int /*<<< orphan*/  DMDISTATE ; 
 int /*<<< orphan*/  DMDT0M ; 
 int FALSE ; 
 int /*<<< orphan*/  SCAN_ENABLE ; 
 int /*<<< orphan*/  SFRLOW0 ; 
 int /*<<< orphan*/  SFRLOW1 ; 
 int /*<<< orphan*/  SFRSTEP ; 
 int /*<<< orphan*/  SFRUP0 ; 
 int /*<<< orphan*/  SFRUP1 ; 
 int /*<<< orphan*/  TMGCFG ; 
 int /*<<< orphan*/  TMGLOCK_QUALITY ; 
 int /*<<< orphan*/  TMGTHFALL ; 
 int /*<<< orphan*/  TMGTHRISE ; 
 int TRUE ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stv0900_get_bits (struct stv0900_internal*,int /*<<< orphan*/ ) ; 
 int stv0900_get_symbol_rate (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 
 int stv0900_read_reg (struct stv0900_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_set_tuner (struct dvb_frontend*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stv0900_set_tuner_auto (struct stv0900_internal*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv0900_write_bits (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stv0900_write_reg (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 stv0900_search_srate_coarse(struct dvb_frontend *fe)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *intp = state->internal;
	enum fe_stv0900_demod_num demod = state->demod;
	int timing_lck = FALSE;
	s32 i, timingcpt = 0,
		direction = 1,
		nb_steps,
		current_step = 0,
		tuner_freq;
	u32 agc2_th,
		coarse_srate = 0,
		agc2_integr = 0,
		currier_step = 1200;

	if (intp->chip_id >= 0x30)
		agc2_th = 0x2e00;
	else
		agc2_th = 0x1f00;

	stv0900_write_bits(intp, DEMOD_MODE, 0x1f);
	stv0900_write_reg(intp, TMGCFG, 0x12);
	stv0900_write_reg(intp, TMGTHRISE, 0xf0);
	stv0900_write_reg(intp, TMGTHFALL, 0xe0);
	stv0900_write_bits(intp, SCAN_ENABLE, 1);
	stv0900_write_bits(intp, CFR_AUTOSCAN, 1);
	stv0900_write_reg(intp, SFRUP1, 0x83);
	stv0900_write_reg(intp, SFRUP0, 0xc0);
	stv0900_write_reg(intp, SFRLOW1, 0x82);
	stv0900_write_reg(intp, SFRLOW0, 0xa0);
	stv0900_write_reg(intp, DMDT0M, 0x0);
	stv0900_write_reg(intp, AGC2REF, 0x50);

	if (intp->chip_id >= 0x30) {
		stv0900_write_reg(intp, CARFREQ, 0x99);
		stv0900_write_reg(intp, SFRSTEP, 0x98);
	} else if (intp->chip_id >= 0x20) {
		stv0900_write_reg(intp, CARFREQ, 0x6a);
		stv0900_write_reg(intp, SFRSTEP, 0x95);
	} else {
		stv0900_write_reg(intp, CARFREQ, 0xed);
		stv0900_write_reg(intp, SFRSTEP, 0x73);
	}

	if (intp->symbol_rate[demod] <= 2000000)
		currier_step = 1000;
	else if (intp->symbol_rate[demod] <= 5000000)
		currier_step = 2000;
	else if (intp->symbol_rate[demod] <= 12000000)
		currier_step = 3000;
	else
			currier_step = 5000;

	nb_steps = -1 + ((intp->srch_range[demod] / 1000) / currier_step);
	nb_steps /= 2;
	nb_steps = (2 * nb_steps) + 1;

	if (nb_steps < 0)
		nb_steps = 1;
	else if (nb_steps > 10) {
		nb_steps = 11;
		currier_step = (intp->srch_range[demod] / 1000) / 10;
	}

	current_step = 0;
	direction = 1;

	tuner_freq = intp->freq[demod];

	while ((timing_lck == FALSE) && (current_step < nb_steps)) {
		stv0900_write_reg(intp, DMDISTATE, 0x5f);
		stv0900_write_bits(intp, DEMOD_MODE, 0);

		msleep(50);

		for (i = 0; i < 10; i++) {
			if (stv0900_get_bits(intp, TMGLOCK_QUALITY) >= 2)
				timingcpt++;

			agc2_integr += (stv0900_read_reg(intp, AGC2I1) << 8) |
					stv0900_read_reg(intp, AGC2I0);
		}

		agc2_integr /= 10;
		coarse_srate = stv0900_get_symbol_rate(intp, intp->mclk, demod);
		current_step++;
		direction *= -1;

		dprintk("lock: I2C_DEMOD_MODE_FIELD =0. Search started. tuner freq=%d agc2=0x%x srate_coarse=%d tmg_cpt=%d\n",
			tuner_freq, agc2_integr, coarse_srate, timingcpt);

		if ((timingcpt >= 5) &&
				(agc2_integr < agc2_th) &&
				(coarse_srate < 55000000) &&
				(coarse_srate > 850000))
			timing_lck = TRUE;
		else if (current_step < nb_steps) {
			if (direction > 0)
				tuner_freq += (current_step * currier_step);
			else
				tuner_freq -= (current_step * currier_step);

			if (intp->tuner_type[demod] == 3)
				stv0900_set_tuner_auto(intp, tuner_freq,
						intp->bw[demod], demod);
			else
				stv0900_set_tuner(fe, tuner_freq,
						intp->bw[demod]);
		}
	}

	if (timing_lck == FALSE)
		coarse_srate = 0;
	else
		coarse_srate = stv0900_get_symbol_rate(intp, intp->mclk, demod);

	return coarse_srate;
}