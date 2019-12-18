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
struct tda18271_priv {unsigned char* tda18271_regs; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 size_t R_CPD ; 
 size_t R_EB13 ; 
 size_t R_EB14 ; 
 size_t R_EB18 ; 
 size_t R_EB20 ; 
 size_t R_EP1 ; 
 size_t R_EP2 ; 
 size_t R_EP3 ; 
 size_t R_EP4 ; 
 size_t R_MPD ; 
 int /*<<< orphan*/  TDA18271_CAL_PLL ; 
 int /*<<< orphan*/  TDA18271_MAIN_PLL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  tda18271_calc_bp_filter (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  tda18271_calc_cal_pll (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tda18271_calc_gain_taper (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  tda18271_calc_km (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  tda18271_calc_main_pll (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tda18271_calc_rf_band (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  tda18271_charge_pump_source (struct dvb_frontend*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tda18271_read_extended (struct dvb_frontend*) ; 
 int /*<<< orphan*/  tda18271_write_regs (struct dvb_frontend*,size_t,int) ; 

__attribute__((used)) static int tda18271_calibrate_rf(struct dvb_frontend *fe, u32 freq)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	u32 N;

	/* set CAL mode to normal */
	regs[R_EP4]  &= ~0x03;
	tda18271_write_regs(fe, R_EP4, 1);

	/* switch off agc1 */
	regs[R_EP3]  |= 0x40; /* sm_lt = 1 */

	regs[R_EB18] |= 0x03; /* set agc1_gain to 15 dB */
	tda18271_write_regs(fe, R_EB18, 1);

	/* frequency dependent parameters */

	tda18271_calc_bp_filter(fe, &freq);
	tda18271_calc_gain_taper(fe, &freq);
	tda18271_calc_rf_band(fe, &freq);
	tda18271_calc_km(fe, &freq);

	tda18271_write_regs(fe, R_EP1, 3);
	tda18271_write_regs(fe, R_EB13, 1);

	/* main pll charge pump source */
	tda18271_charge_pump_source(fe, TDA18271_MAIN_PLL, 1);

	/* cal pll charge pump source */
	tda18271_charge_pump_source(fe, TDA18271_CAL_PLL, 1);

	/* force dcdc converter to 0 V */
	regs[R_EB14] = 0x00;
	tda18271_write_regs(fe, R_EB14, 1);

	/* disable plls lock */
	regs[R_EB20] &= ~0x20;
	tda18271_write_regs(fe, R_EB20, 1);

	/* set CAL mode to RF tracking filter calibration */
	regs[R_EP4]  |= 0x03;
	tda18271_write_regs(fe, R_EP4, 2);

	/* --------------------------------------------------------------- */

	/* set the internal calibration signal */
	N = freq;

	tda18271_calc_cal_pll(fe, N);
	tda18271_write_regs(fe, R_CPD, 4);

	/* downconvert internal calibration */
	N += 1000000;

	tda18271_calc_main_pll(fe, N);
	tda18271_write_regs(fe, R_MPD, 4);

	msleep(5);

	tda18271_write_regs(fe, R_EP2, 1);
	tda18271_write_regs(fe, R_EP1, 1);
	tda18271_write_regs(fe, R_EP2, 1);
	tda18271_write_regs(fe, R_EP1, 1);

	/* --------------------------------------------------------------- */

	/* normal operation for the main pll */
	tda18271_charge_pump_source(fe, TDA18271_MAIN_PLL, 0);

	/* normal operation for the cal pll  */
	tda18271_charge_pump_source(fe, TDA18271_CAL_PLL, 0);

	msleep(10); /* plls locking */

	/* launch the rf tracking filters calibration */
	regs[R_EB20]  |= 0x20;
	tda18271_write_regs(fe, R_EB20, 1);

	msleep(60); /* calibration */

	/* --------------------------------------------------------------- */

	/* set CAL mode to normal */
	regs[R_EP4]  &= ~0x03;

	/* switch on agc1 */
	regs[R_EP3]  &= ~0x40; /* sm_lt = 0 */

	regs[R_EB18] &= ~0x03; /* set agc1_gain to  6 dB */
	tda18271_write_regs(fe, R_EB18, 1);

	tda18271_write_regs(fe, R_EP3, 2);

	/* synchronization */
	tda18271_write_regs(fe, R_EP1, 1);

	/* get calibration result */
	tda18271_read_extended(fe);

	return regs[R_EB14];
}