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
typedef  int u8 ;
typedef  int u32 ;
struct stb0899_internal {int master_clk; int srate; } ;
struct stb0899_state {struct stb0899_internal internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTR_CNTRL ; 
 int /*<<< orphan*/  BTR_FREQ_CORR ; 
 int Log2Int (int) ; 
 int /*<<< orphan*/  STB0899_BASE_ANTI_ALIAS_SEL ; 
 int /*<<< orphan*/  STB0899_BASE_BTR_CNTRL ; 
 int /*<<< orphan*/  STB0899_BASE_BTR_NOM_FREQ ; 
 int /*<<< orphan*/  STB0899_BASE_DECIM_CNTRL ; 
 int /*<<< orphan*/  STB0899_BASE_FREQ_ADJ_SCALE ; 
 int /*<<< orphan*/  STB0899_OFF0_ANTI_ALIAS_SEL ; 
 int /*<<< orphan*/  STB0899_OFF0_BTR_CNTRL ; 
 int /*<<< orphan*/  STB0899_OFF0_BTR_NOM_FREQ ; 
 int /*<<< orphan*/  STB0899_OFF0_DECIM_CNTRL ; 
 int /*<<< orphan*/  STB0899_OFF0_FREQ_ADJ_SCALE ; 
 int STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int,int) ; 
 int stb0899_dvbs2_calc_dev (struct stb0899_state*) ; 
 int stb0899_dvbs2_calc_srate (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_write_s2reg (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stb0899_dvbs2_set_srate(struct stb0899_state *state)
{
	struct stb0899_internal *internal = &state->internal;

	u32 dec_ratio, dec_rate, win_sel, decim, f_sym, btr_nom_freq;
	u32 correction, freq_adj, band_lim, decim_cntrl, reg;
	u8 anti_alias;

	/*set decimation to 1*/
	dec_ratio = (internal->master_clk * 2) / (5 * internal->srate);
	dec_ratio = (dec_ratio == 0) ? 1 : dec_ratio;
	dec_rate = Log2Int(dec_ratio);

	win_sel = 0;
	if (dec_rate >= 5)
		win_sel = dec_rate - 4;

	decim = (1 << dec_rate);
	/* (FSamp/Fsymbol *100) for integer Calculation */
	f_sym = internal->master_clk / ((decim * internal->srate) / 1000);

	if (f_sym <= 2250)	/* don't band limit signal going into btr block*/
		band_lim = 1;
	else
		band_lim = 0;	/* band limit signal going into btr block*/

	decim_cntrl = ((win_sel << 3) & 0x18) + ((band_lim << 5) & 0x20) + (dec_rate & 0x7);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_DECIM_CNTRL, STB0899_OFF0_DECIM_CNTRL, decim_cntrl);

	if (f_sym <= 3450)
		anti_alias = 0;
	else if (f_sym <= 4250)
		anti_alias = 1;
	else
		anti_alias = 2;

	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_ANTI_ALIAS_SEL, STB0899_OFF0_ANTI_ALIAS_SEL, anti_alias);
	btr_nom_freq = stb0899_dvbs2_calc_srate(state);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_NOM_FREQ, STB0899_OFF0_BTR_NOM_FREQ, btr_nom_freq);

	correction = stb0899_dvbs2_calc_dev(state);
	reg = STB0899_READ_S2REG(STB0899_S2DEMOD, BTR_CNTRL);
	STB0899_SETFIELD_VAL(BTR_FREQ_CORR, reg, correction);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_BTR_CNTRL, STB0899_OFF0_BTR_CNTRL, reg);

	/* scale UWP+CSM frequency to sample rate*/
	freq_adj =  internal->srate / (internal->master_clk / 4096);
	stb0899_write_s2reg(state, STB0899_S2DEMOD, STB0899_BASE_FREQ_ADJ_SCALE, STB0899_OFF0_FREQ_ADJ_SCALE, freq_adj);
}