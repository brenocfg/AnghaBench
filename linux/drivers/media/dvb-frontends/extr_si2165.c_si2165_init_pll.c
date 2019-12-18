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
typedef  unsigned int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int ref_freq_hz; } ;
struct si2165_state {int fvco_hz; unsigned int adc_clk; unsigned int sys_clk; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_PLL_DIVL ; 
 int si2165_write (struct si2165_state*,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static int si2165_init_pll(struct si2165_state *state)
{
	u32 ref_freq_hz = state->config.ref_freq_hz;
	u8 divr = 1; /* 1..7 */
	u8 divp = 1; /* only 1 or 4 */
	u8 divn = 56; /* 1..63 */
	u8 divm = 8;
	u8 divl = 12;
	u8 buf[4];

	/*
	 * hardcoded values can be deleted if calculation is verified
	 * or it yields the same values as the windows driver
	 */
	switch (ref_freq_hz) {
	case 16000000u:
		divn = 56;
		break;
	case 24000000u:
		divr = 2;
		divp = 4;
		divn = 19;
		break;
	default:
		/* ref_freq / divr must be between 4 and 16 MHz */
		if (ref_freq_hz > 16000000u)
			divr = 2;

		/*
		 * now select divn and divp such that
		 * fvco is in 1624..1824 MHz
		 */
		if (1624000000u * divr > ref_freq_hz * 2u * 63u)
			divp = 4;

		/* is this already correct regarding rounding? */
		divn = 1624000000u * divr / (ref_freq_hz * 2u * divp);
		break;
	}

	/* adc_clk and sys_clk depend on xtal and pll settings */
	state->fvco_hz = ref_freq_hz / divr
			* 2u * divn * divp;
	state->adc_clk = state->fvco_hz / (divm * 4u);
	state->sys_clk = state->fvco_hz / (divl * 2u);

	/* write all 4 pll registers 0x00a0..0x00a3 at once */
	buf[0] = divl;
	buf[1] = divm;
	buf[2] = (divn & 0x3f) | ((divp == 1) ? 0x40 : 0x00) | 0x80;
	buf[3] = divr;
	return si2165_write(state, REG_PLL_DIVL, buf, 4);
}