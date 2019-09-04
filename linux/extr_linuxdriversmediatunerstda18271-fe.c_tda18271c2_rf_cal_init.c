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
struct tda18271_priv {unsigned char* tda18271_regs; int cal_initialized; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 size_t R_EP1 ; 
 int tda18271_calc_rf_filter_curve (struct dvb_frontend*) ; 
 int tda18271_por (struct dvb_frontend*) ; 
 scalar_t__ tda_fail (int) ; 
 int /*<<< orphan*/  tda_info (char*) ; 

__attribute__((used)) static int tda18271c2_rf_cal_init(struct dvb_frontend *fe)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	int ret;

	/* test RF_CAL_OK to see if we need init */
	if ((regs[R_EP1] & 0x10) == 0)
		priv->cal_initialized = false;

	if (priv->cal_initialized)
		return 0;

	ret = tda18271_calc_rf_filter_curve(fe);
	if (tda_fail(ret))
		goto fail;

	ret = tda18271_por(fe);
	if (tda_fail(ret))
		goto fail;

	tda_info("RF tracking filter calibration complete\n");

	priv->cal_initialized = true;
	goto end;
fail:
	tda_info("RF tracking filter calibration failed!\n");
end:
	return ret;
}