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
struct lme2510_state {int tuner_config; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; } ;
struct dvb_usb_adapter {int /*<<< orphan*/ * fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_PLL_OPERA1 ; 
 int ENODEV ; 
#define  TUNER_LG 131 
#define  TUNER_RS2000 130 
#define  TUNER_S0194 129 
#define  TUNER_S7395 128 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct lme2510_state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  dvb_pll_attach ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  ix2505v_attach ; 
 int lme2510_int_read (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  lme_tuner ; 
 int /*<<< orphan*/  tda826x_attach ; 
 int /*<<< orphan*/  ts2020_attach ; 
 int /*<<< orphan*/  ts2020_config ; 

__attribute__((used)) static int dm04_lme2510_tuner(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *d = adap_to_d(adap);
	struct lme2510_state *st = adap_to_priv(adap);
	static const char * const tun_msg[] = {"", "TDA8263", "IX2505V", "DVB_PLL_OPERA", "RS2000"};
	int ret = 0;

	switch (st->tuner_config) {
	case TUNER_LG:
		if (dvb_attach(tda826x_attach, adap->fe[0], 0x60,
			&d->i2c_adap, 1))
			ret = st->tuner_config;
		break;
	case TUNER_S7395:
		if (dvb_attach(ix2505v_attach , adap->fe[0], &lme_tuner,
			&d->i2c_adap))
			ret = st->tuner_config;
		break;
	case TUNER_S0194:
		if (dvb_attach(dvb_pll_attach , adap->fe[0], 0x60,
			&d->i2c_adap, DVB_PLL_OPERA1))
			ret = st->tuner_config;
		break;
	case TUNER_RS2000:
		if (dvb_attach(ts2020_attach, adap->fe[0],
			       &ts2020_config, &d->i2c_adap))
			ret = st->tuner_config;
		break;
	default:
		break;
	}

	if (ret) {
		info("TUN Found %s tuner", tun_msg[ret]);
	} else {
		info("TUN No tuner found");
		return -ENODEV;
	}

	/* Start the Interrupt*/
	ret = lme2510_int_read(adap);
	if (ret < 0) {
		info("INT Unable to start Interrupt Service");
		return -ENODEV;
	}

	return ret;
}