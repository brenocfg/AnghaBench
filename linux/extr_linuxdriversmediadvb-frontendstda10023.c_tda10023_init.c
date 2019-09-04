#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tda10023_state {TYPE_2__* config; int /*<<< orphan*/  pll_n; int /*<<< orphan*/  pll_p; int /*<<< orphan*/  pll_m; } ;
struct dvb_frontend {TYPE_1__* dvb; struct tda10023_state* demodulator_priv; } ;
struct TYPE_4__ {int deltaf; int output_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int REG0_INIT_VAL ; 
 int TDA10023_OUTPUT_MODE_PARALLEL_B ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda10023_writetab (struct tda10023_state*,int*) ; 

__attribute__((used)) static int tda10023_init (struct dvb_frontend *fe)
{
	struct tda10023_state* state = fe->demodulator_priv;
	u8 tda10023_inittab[] = {
/*        reg  mask val */
/* 000 */ 0x2a, 0xff, 0x02,  /* PLL3, Bypass, Power Down */
/* 003 */ 0xff, 0x64, 0x00,  /* Sleep 100ms */
/* 006 */ 0x2a, 0xff, 0x03,  /* PLL3, Bypass, Power Down */
/* 009 */ 0xff, 0x64, 0x00,  /* Sleep 100ms */
			   /* PLL1 */
/* 012 */ 0x28, 0xff, (state->pll_m-1),
			   /* PLL2 */
/* 015 */ 0x29, 0xff, ((state->pll_p-1)<<6)|(state->pll_n-1),
			   /* GPR FSAMPLING=1 */
/* 018 */ 0x00, 0xff, REG0_INIT_VAL,
/* 021 */ 0x2a, 0xff, 0x08,  /* PLL3 PSACLK=1 */
/* 024 */ 0xff, 0x64, 0x00,  /* Sleep 100ms */
/* 027 */ 0x1f, 0xff, 0x00,  /* RESET */
/* 030 */ 0xff, 0x64, 0x00,  /* Sleep 100ms */
/* 033 */ 0xe6, 0x0c, 0x04,  /* RSCFG_IND */
/* 036 */ 0x10, 0xc0, 0x80,  /* DECDVBCFG1 PBER=1 */

/* 039 */ 0x0e, 0xff, 0x82,  /* GAIN1 */
/* 042 */ 0x03, 0x08, 0x08,  /* CLKCONF DYN=1 */
/* 045 */ 0x2e, 0xbf, 0x30,  /* AGCCONF2 TRIAGC=0,POSAGC=ENAGCIF=1
				       PPWMTUN=0 PPWMIF=0 */
/* 048 */ 0x01, 0xff, 0x30,  /* AGCREF */
/* 051 */ 0x1e, 0x84, 0x84,  /* CONTROL SACLK_ON=1 */
/* 054 */ 0x1b, 0xff, 0xc8,  /* ADC TWOS=1 */
/* 057 */ 0x3b, 0xff, 0xff,  /* IFMAX */
/* 060 */ 0x3c, 0xff, 0x00,  /* IFMIN */
/* 063 */ 0x34, 0xff, 0x00,  /* PWMREF */
/* 066 */ 0x35, 0xff, 0xff,  /* TUNMAX */
/* 069 */ 0x36, 0xff, 0x00,  /* TUNMIN */
/* 072 */ 0x06, 0xff, 0x7f,  /* EQCONF1 POSI=7 ENADAPT=ENEQUAL=DFE=1 */
/* 075 */ 0x1c, 0x30, 0x30,  /* EQCONF2 STEPALGO=SGNALGO=1 */
/* 078 */ 0x37, 0xff, 0xf6,  /* DELTAF_LSB */
/* 081 */ 0x38, 0xff, 0xff,  /* DELTAF_MSB */
/* 084 */ 0x02, 0xff, 0x93,  /* AGCCONF1  IFS=1 KAGCIF=2 KAGCTUN=3 */
/* 087 */ 0x2d, 0xff, 0xf6,  /* SWEEP SWPOS=1 SWDYN=7 SWSTEP=1 SWLEN=2 */
/* 090 */ 0x04, 0x10, 0x00,  /* SWRAMP=1 */
/* 093 */ 0x12, 0xff, TDA10023_OUTPUT_MODE_PARALLEL_B, /*
				INTP1 POCLKP=1 FEL=1 MFS=0 */
/* 096 */ 0x2b, 0x01, 0xa1,  /* INTS1 */
/* 099 */ 0x20, 0xff, 0x04,  /* INTP2 SWAPP=? MSBFIRSTP=? INTPSEL=? */
/* 102 */ 0x2c, 0xff, 0x0d,  /* INTP/S TRIP=0 TRIS=0 */
/* 105 */ 0xc4, 0xff, 0x00,
/* 108 */ 0xc3, 0x30, 0x00,
/* 111 */ 0xb5, 0xff, 0x19,  /* ERAGC_THD */
/* 114 */ 0x00, 0x03, 0x01,  /* GPR, CLBS soft reset */
/* 117 */ 0x00, 0x03, 0x03,  /* GPR, CLBS soft reset */
/* 120 */ 0xff, 0x64, 0x00,  /* Sleep 100ms */
/* 123 */ 0xff, 0xff, 0xff
};
	dprintk("DVB: TDA10023(%d): init chip\n", fe->dvb->num);

	/* override default values if set in config */
	if (state->config->deltaf) {
		tda10023_inittab[80] = (state->config->deltaf & 0xff);
		tda10023_inittab[83] = (state->config->deltaf >> 8);
	}

	if (state->config->output_mode)
		tda10023_inittab[95] = state->config->output_mode;

	tda10023_writetab(state, tda10023_inittab);

	return 0;
}