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
typedef  int /*<<< orphan*/  u32 ;
struct tda18271_priv {unsigned char* tda18271_regs; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_CAL ; 
 size_t R_EB14 ; 
 int tda18271_lookup_map (struct dvb_frontend*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*) ; 

int tda18271_calc_rf_cal(struct dvb_frontend *fe, u32 *freq)
{
	/* sets rf cal byte (RFC_Cprog), but does not write it */
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	u8 val;

	int ret = tda18271_lookup_map(fe, RF_CAL, freq, &val);
	/* The TDA18271HD/C1 rf_cal map lookup is expected to go out of range
	 * for frequencies above 61.1 MHz.  In these cases, the internal RF
	 * tracking filters calibration mechanism is used.
	 *
	 * There is no need to warn the user about this.
	 */
	if (ret < 0)
		goto fail;

	regs[R_EB14] = val;
fail:
	return ret;
}