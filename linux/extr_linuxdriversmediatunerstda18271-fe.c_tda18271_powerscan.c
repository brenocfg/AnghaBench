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
typedef  unsigned char u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct tda18271_priv {unsigned char* tda18271_regs; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 size_t R_EB10 ; 
 size_t R_EB14 ; 
 size_t R_EP2 ; 
 size_t R_EP4 ; 
 size_t R_MPD ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  tda18271_calc_gain_taper (struct dvb_frontend*,scalar_t__*) ; 
 int /*<<< orphan*/  tda18271_calc_main_pll (struct dvb_frontend*,scalar_t__) ; 
 int /*<<< orphan*/  tda18271_calc_rf_band (struct dvb_frontend*,scalar_t__*) ; 
 int /*<<< orphan*/  tda18271_calc_rf_cal (struct dvb_frontend*,scalar_t__*) ; 
 int /*<<< orphan*/  tda18271_lookup_cid_target (struct dvb_frontend*,scalar_t__*,unsigned char*,int*) ; 
 int tda18271_read_extended (struct dvb_frontend*) ; 
 int /*<<< orphan*/  tda18271_write_regs (struct dvb_frontend*,size_t,int) ; 
 int /*<<< orphan*/  tda_cal (char*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ tda_fail (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tda18271_powerscan(struct dvb_frontend *fe,
			      u32 *freq_in, u32 *freq_out)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	int sgn, bcal, count, wait, ret;
	u8 cid_target;
	u16 count_limit;
	u32 freq;

	freq = *freq_in;

	tda18271_calc_rf_band(fe, &freq);
	tda18271_calc_rf_cal(fe, &freq);
	tda18271_calc_gain_taper(fe, &freq);
	tda18271_lookup_cid_target(fe, &freq, &cid_target, &count_limit);

	tda18271_write_regs(fe, R_EP2, 1);
	tda18271_write_regs(fe, R_EB14, 1);

	/* downconvert frequency */
	freq += 1000000;

	tda18271_calc_main_pll(fe, freq);
	tda18271_write_regs(fe, R_MPD, 4);

	msleep(5); /* pll locking */

	/* detection mode */
	regs[R_EP4]  &= ~0x03;
	regs[R_EP4]  |= 0x01;
	tda18271_write_regs(fe, R_EP4, 1);

	/* launch power detection measurement */
	tda18271_write_regs(fe, R_EP2, 1);

	/* read power detection info, stored in EB10 */
	ret = tda18271_read_extended(fe);
	if (tda_fail(ret))
		return ret;

	/* algorithm initialization */
	sgn = 1;
	*freq_out = *freq_in;
	bcal = 0;
	count = 0;
	wait = false;

	while ((regs[R_EB10] & 0x3f) < cid_target) {
		/* downconvert updated freq to 1 MHz */
		freq = *freq_in + (sgn * count) + 1000000;

		tda18271_calc_main_pll(fe, freq);
		tda18271_write_regs(fe, R_MPD, 4);

		if (wait) {
			msleep(5); /* pll locking */
			wait = false;
		} else
			udelay(100); /* pll locking */

		/* launch power detection measurement */
		tda18271_write_regs(fe, R_EP2, 1);

		/* read power detection info, stored in EB10 */
		ret = tda18271_read_extended(fe);
		if (tda_fail(ret))
			return ret;

		count += 200;

		if (count <= count_limit)
			continue;

		if (sgn <= 0)
			break;

		sgn = -1 * sgn;
		count = 200;
		wait = true;
	}

	if ((regs[R_EB10] & 0x3f) >= cid_target) {
		bcal = 1;
		*freq_out = freq - 1000000;
	} else
		bcal = 0;

	tda_cal("bcal = %d, freq_in = %d, freq_out = %d (freq = %d)\n",
		bcal, *freq_in, *freq_out, freq);

	return bcal;
}