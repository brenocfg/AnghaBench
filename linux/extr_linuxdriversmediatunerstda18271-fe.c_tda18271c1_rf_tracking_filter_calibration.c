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
struct tda18271_priv {unsigned char* tda18271_regs; int mode; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 size_t R_EB13 ; 
 size_t R_EB14 ; 
 size_t R_EB20 ; 
 size_t R_EB4 ; 
 size_t R_EB7 ; 
 size_t R_EP1 ; 
 size_t R_EP2 ; 
 size_t R_EP3 ; 
 size_t R_EP4 ; 
#define  TDA18271_ANALOG 129 
#define  TDA18271_DIGITAL 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  tda18271_calc_bp_filter (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  tda18271_calc_cal_pll (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tda18271_calc_gain_taper (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  tda18271_calc_km (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  tda18271_calc_main_pll (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tda18271_calc_rf_band (struct dvb_frontend*,int*) ; 
 scalar_t__ tda18271_calc_rf_cal (struct dvb_frontend*,int*) ; 
 int tda18271_write_regs (struct dvb_frontend*,size_t,int) ; 
 scalar_t__ tda_fail (int) ; 

__attribute__((used)) static int tda18271c1_rf_tracking_filter_calibration(struct dvb_frontend *fe,
						     u32 freq, u32 bw)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	int ret;
	u32 N = 0;

	/* calculate bp filter */
	tda18271_calc_bp_filter(fe, &freq);
	tda18271_write_regs(fe, R_EP1, 1);

	regs[R_EB4]  &= 0x07;
	regs[R_EB4]  |= 0x60;
	tda18271_write_regs(fe, R_EB4, 1);

	regs[R_EB7]   = 0x60;
	tda18271_write_regs(fe, R_EB7, 1);

	regs[R_EB14]  = 0x00;
	tda18271_write_regs(fe, R_EB14, 1);

	regs[R_EB20]  = 0xcc;
	tda18271_write_regs(fe, R_EB20, 1);

	/* set cal mode to RF tracking filter calibration */
	regs[R_EP4]  |= 0x03;

	/* calculate cal pll */

	switch (priv->mode) {
	case TDA18271_ANALOG:
		N = freq - 1250000;
		break;
	case TDA18271_DIGITAL:
		N = freq + bw / 2;
		break;
	}

	tda18271_calc_cal_pll(fe, N);

	/* calculate main pll */

	switch (priv->mode) {
	case TDA18271_ANALOG:
		N = freq - 250000;
		break;
	case TDA18271_DIGITAL:
		N = freq + bw / 2 + 1000000;
		break;
	}

	tda18271_calc_main_pll(fe, N);

	ret = tda18271_write_regs(fe, R_EP3, 11);
	if (tda_fail(ret))
		return ret;

	msleep(5); /* RF tracking filter calibration initialization */

	/* search for K,M,CO for RF calibration */
	tda18271_calc_km(fe, &freq);
	tda18271_write_regs(fe, R_EB13, 1);

	/* search for rf band */
	tda18271_calc_rf_band(fe, &freq);

	/* search for gain taper */
	tda18271_calc_gain_taper(fe, &freq);

	tda18271_write_regs(fe, R_EP2, 1);
	tda18271_write_regs(fe, R_EP1, 1);
	tda18271_write_regs(fe, R_EP2, 1);
	tda18271_write_regs(fe, R_EP1, 1);

	regs[R_EB4]  &= 0x07;
	regs[R_EB4]  |= 0x40;
	tda18271_write_regs(fe, R_EB4, 1);

	regs[R_EB7]   = 0x40;
	tda18271_write_regs(fe, R_EB7, 1);
	msleep(10); /* pll locking */

	regs[R_EB20]  = 0xec;
	tda18271_write_regs(fe, R_EB20, 1);
	msleep(60); /* RF tracking filter calibration completion */

	regs[R_EP4]  &= ~0x03; /* set cal mode to normal */
	tda18271_write_regs(fe, R_EP4, 1);

	tda18271_write_regs(fe, R_EP1, 1);

	/* RF tracking filter correction for VHF_Low band */
	if (0 == tda18271_calc_rf_cal(fe, &freq))
		tda18271_write_regs(fe, R_EB14, 1);

	return 0;
}