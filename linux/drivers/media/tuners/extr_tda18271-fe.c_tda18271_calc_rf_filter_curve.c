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
struct tda18271_priv {int /*<<< orphan*/  tm_rfcal; TYPE_1__* rf_cal_state; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;
struct TYPE_2__ {int rfmax; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int tda18271_powerscan_init (struct dvb_frontend*) ; 
 int /*<<< orphan*/  tda18271_read_thermometer (struct dvb_frontend*) ; 
 int tda18271_rf_tracking_filters_init (struct dvb_frontend*,int) ; 
 scalar_t__ tda_fail (int) ; 
 int /*<<< orphan*/  tda_info (char*) ; 

__attribute__((used)) static int tda18271_calc_rf_filter_curve(struct dvb_frontend *fe)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned int i;
	int ret;

	tda_info("performing RF tracking filter calibration\n");

	/* wait for die temperature stabilization */
	msleep(200);

	ret = tda18271_powerscan_init(fe);
	if (tda_fail(ret))
		goto fail;

	/* rf band calibration */
	for (i = 0; priv->rf_cal_state[i].rfmax != 0; i++) {
		ret =
		tda18271_rf_tracking_filters_init(fe, 1000 *
						  priv->rf_cal_state[i].rfmax);
		if (tda_fail(ret))
			goto fail;
	}

	priv->tm_rfcal = tda18271_read_thermometer(fe);
fail:
	return ret;
}