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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long long u64 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct adf4350_state {unsigned long long min_out_freq; int r4_rf_div_sel; int chspc; scalar_t__ r0_int; int r1_mod; int fpfd; int r0_fract; int* regs; unsigned long long freq_req; TYPE_1__* spi; struct adf4350_platform_data* pdata; } ;
struct adf4350_platform_data {scalar_t__ ref_div_factor; int r2_user_settings; int r3_user_settings; int r4_user_settings; scalar_t__ ref_div2_en; scalar_t__ ref_doubler_en; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADF4350_MAX_BANDSEL_CLK ; 
 unsigned long long ADF4350_MAX_FREQ_45_PRESC ; 
 int ADF4350_MAX_MODULUS ; 
 unsigned long long ADF4350_MAX_OUT_FREQ ; 
 scalar_t__ ADF4350_MAX_R_CNT ; 
 unsigned long long ADF4350_MIN_VCO_FREQ ; 
 size_t ADF4350_REG0 ; 
 int ADF4350_REG0_FRACT (int) ; 
 int ADF4350_REG0_INT (unsigned long long) ; 
 size_t ADF4350_REG1 ; 
 int ADF4350_REG1_MOD (int) ; 
 int ADF4350_REG1_PHASE (int) ; 
 int ADF4350_REG1_PRESCALER ; 
 size_t ADF4350_REG2 ; 
 int ADF4350_REG2_10BIT_R_CNT (scalar_t__) ; 
 int ADF4350_REG2_CHARGE_PUMP_CURR_uA (int) ; 
 int ADF4350_REG2_DOUBLE_BUFF_EN ; 
 int ADF4350_REG2_LDF_INT_N ; 
 int ADF4350_REG2_LDP_6ns ; 
 int ADF4350_REG2_MUXOUT (int) ; 
 int ADF4350_REG2_NOISE_MODE (int) ; 
 int ADF4350_REG2_PD_POLARITY_POS ; 
 int ADF4350_REG2_RDIV2_EN ; 
 int ADF4350_REG2_RMULT2_EN ; 
 size_t ADF4350_REG3 ; 
 int ADF4350_REG3_12BIT_CLKDIV (int) ; 
 int ADF4350_REG3_12BIT_CLKDIV_MODE (int) ; 
 int ADF4350_REG3_12BIT_CSR_EN ; 
 size_t ADF4350_REG4 ; 
 int ADF4350_REG4_8BIT_BAND_SEL_CLKDIV (int /*<<< orphan*/ ) ; 
 int ADF4350_REG4_AUX_OUTPUT_EN ; 
 int ADF4350_REG4_AUX_OUTPUT_FUND ; 
 int ADF4350_REG4_AUX_OUTPUT_PWR (int) ; 
 int ADF4350_REG4_FEEDBACK_FUND ; 
 int ADF4350_REG4_MUTE_TILL_LOCK_EN ; 
 int ADF4350_REG4_OUTPUT_PWR (int) ; 
 int ADF4350_REG4_RF_DIV_SEL (int) ; 
 int ADF4350_REG4_RF_OUT_EN ; 
 size_t ADF4350_REG5 ; 
 int ADF4350_REG5_LD_PIN_MODE_DIGITAL ; 
 int ADF4351_REG3_ANTI_BACKLASH_3ns_EN ; 
 int ADF4351_REG3_BAND_SEL_CLOCK_MODE_HIGH ; 
 int ADF4351_REG3_CHARGE_CANCELLATION_EN ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int adf4350_sync_config (struct adf4350_state*) ; 
 scalar_t__ adf4350_tune_r_cnt (struct adf4350_state*,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long long,int,scalar_t__,unsigned long long,int,int,int,char*,int /*<<< orphan*/ ) ; 
 int do_div (unsigned long long,int) ; 
 int gcd (int,int) ; 

__attribute__((used)) static int adf4350_set_freq(struct adf4350_state *st, unsigned long long freq)
{
	struct adf4350_platform_data *pdata = st->pdata;
	u64 tmp;
	u32 div_gcd, prescaler, chspc;
	u16 mdiv, r_cnt = 0;
	u8 band_sel_div;

	if (freq > ADF4350_MAX_OUT_FREQ || freq < st->min_out_freq)
		return -EINVAL;

	if (freq > ADF4350_MAX_FREQ_45_PRESC) {
		prescaler = ADF4350_REG1_PRESCALER;
		mdiv = 75;
	} else {
		prescaler = 0;
		mdiv = 23;
	}

	st->r4_rf_div_sel = 0;

	while (freq < ADF4350_MIN_VCO_FREQ) {
		freq <<= 1;
		st->r4_rf_div_sel++;
	}

	/*
	 * Allow a predefined reference division factor
	 * if not set, compute our own
	 */
	if (pdata->ref_div_factor)
		r_cnt = pdata->ref_div_factor - 1;

	chspc = st->chspc;

	do  {
		do {
			do {
				r_cnt = adf4350_tune_r_cnt(st, r_cnt);
				st->r1_mod = st->fpfd / chspc;
				if (r_cnt > ADF4350_MAX_R_CNT) {
					/* try higher spacing values */
					chspc++;
					r_cnt = 0;
				}
			} while ((st->r1_mod > ADF4350_MAX_MODULUS) && r_cnt);
		} while (r_cnt == 0);

		tmp = freq * (u64)st->r1_mod + (st->fpfd >> 1);
		do_div(tmp, st->fpfd); /* Div round closest (n + d/2)/d */
		st->r0_fract = do_div(tmp, st->r1_mod);
		st->r0_int = tmp;
	} while (mdiv > st->r0_int);

	band_sel_div = DIV_ROUND_UP(st->fpfd, ADF4350_MAX_BANDSEL_CLK);

	if (st->r0_fract && st->r1_mod) {
		div_gcd = gcd(st->r1_mod, st->r0_fract);
		st->r1_mod /= div_gcd;
		st->r0_fract /= div_gcd;
	} else {
		st->r0_fract = 0;
		st->r1_mod = 1;
	}

	dev_dbg(&st->spi->dev, "VCO: %llu Hz, PFD %lu Hz\n"
		"REF_DIV %d, R0_INT %d, R0_FRACT %d\n"
		"R1_MOD %d, RF_DIV %d\nPRESCALER %s, BAND_SEL_DIV %d\n",
		freq, st->fpfd, r_cnt, st->r0_int, st->r0_fract, st->r1_mod,
		1 << st->r4_rf_div_sel, prescaler ? "8/9" : "4/5",
		band_sel_div);

	st->regs[ADF4350_REG0] = ADF4350_REG0_INT(st->r0_int) |
				 ADF4350_REG0_FRACT(st->r0_fract);

	st->regs[ADF4350_REG1] = ADF4350_REG1_PHASE(1) |
				 ADF4350_REG1_MOD(st->r1_mod) |
				 prescaler;

	st->regs[ADF4350_REG2] =
		ADF4350_REG2_10BIT_R_CNT(r_cnt) |
		ADF4350_REG2_DOUBLE_BUFF_EN |
		(pdata->ref_doubler_en ? ADF4350_REG2_RMULT2_EN : 0) |
		(pdata->ref_div2_en ? ADF4350_REG2_RDIV2_EN : 0) |
		(pdata->r2_user_settings & (ADF4350_REG2_PD_POLARITY_POS |
		ADF4350_REG2_LDP_6ns | ADF4350_REG2_LDF_INT_N |
		ADF4350_REG2_CHARGE_PUMP_CURR_uA(5000) |
		ADF4350_REG2_MUXOUT(0x7) | ADF4350_REG2_NOISE_MODE(0x3)));

	st->regs[ADF4350_REG3] = pdata->r3_user_settings &
				 (ADF4350_REG3_12BIT_CLKDIV(0xFFF) |
				 ADF4350_REG3_12BIT_CLKDIV_MODE(0x3) |
				 ADF4350_REG3_12BIT_CSR_EN |
				 ADF4351_REG3_CHARGE_CANCELLATION_EN |
				 ADF4351_REG3_ANTI_BACKLASH_3ns_EN |
				 ADF4351_REG3_BAND_SEL_CLOCK_MODE_HIGH);

	st->regs[ADF4350_REG4] =
		ADF4350_REG4_FEEDBACK_FUND |
		ADF4350_REG4_RF_DIV_SEL(st->r4_rf_div_sel) |
		ADF4350_REG4_8BIT_BAND_SEL_CLKDIV(band_sel_div) |
		ADF4350_REG4_RF_OUT_EN |
		(pdata->r4_user_settings &
		(ADF4350_REG4_OUTPUT_PWR(0x3) |
		ADF4350_REG4_AUX_OUTPUT_PWR(0x3) |
		ADF4350_REG4_AUX_OUTPUT_EN |
		ADF4350_REG4_AUX_OUTPUT_FUND |
		ADF4350_REG4_MUTE_TILL_LOCK_EN));

	st->regs[ADF4350_REG5] = ADF4350_REG5_LD_PIN_MODE_DIGITAL;
	st->freq_req = freq;

	return adf4350_sync_config(st);
}