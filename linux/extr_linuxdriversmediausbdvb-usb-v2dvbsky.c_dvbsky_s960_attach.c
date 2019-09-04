#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ts2020_config {int clk; int i2c_wr_max; int ts_clk; int agc; int lnb_hv_pol; int lnb_en_pol; int /*<<< orphan*/  get_agc_pwm; TYPE_3__* fe; struct i2c_adapter* (* get_i2c_adapter ) (void*) ;TYPE_3__* (* get_dvb_frontend ) (void*) ;scalar_t__ ts_clk_pol; int /*<<< orphan*/  ts_mode; scalar_t__ clk_out; } ;
struct m88ds3103_platform_data {int clk; int i2c_wr_max; int ts_clk; int agc; int lnb_hv_pol; int lnb_en_pol; int /*<<< orphan*/  get_agc_pwm; TYPE_3__* fe; struct i2c_adapter* (* get_i2c_adapter ) (void*) ;TYPE_3__* (* get_dvb_frontend ) (void*) ;scalar_t__ ts_clk_pol; int /*<<< orphan*/  ts_mode; scalar_t__ clk_out; } ;
struct i2c_adapter {int dummy; } ;
struct dvbsky_state {int /*<<< orphan*/  fe_set_voltage; int /*<<< orphan*/  fe_read_status; void* i2c_client_demod; void* i2c_client_tuner; } ;
struct dvb_usb_device {struct i2c_adapter i2c_adap; } ;
struct dvb_usb_adapter {TYPE_3__** fe; } ;
struct TYPE_4__ {int /*<<< orphan*/  get_rf_strength; } ;
struct TYPE_5__ {int /*<<< orphan*/  set_voltage; int /*<<< orphan*/  read_status; TYPE_1__ tuner_ops; int /*<<< orphan*/  read_signal_strength; } ;
struct TYPE_6__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  M88DS3103_TS_CI ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct dvbsky_state* adap_to_priv (struct dvb_usb_adapter*) ; 
 void* dvb_module_probe (char*,int /*<<< orphan*/ *,struct i2c_adapter*,int,struct ts2020_config*) ; 
 int /*<<< orphan*/  dvb_module_release (void*) ; 
 int /*<<< orphan*/  dvbsky_usb_read_status ; 
 int /*<<< orphan*/  dvbsky_usb_set_voltage ; 
 int /*<<< orphan*/  m88ds3103_get_agc_pwm ; 
 TYPE_3__* stub1 (void*) ; 
 struct i2c_adapter* stub2 (void*) ; 

__attribute__((used)) static int dvbsky_s960_attach(struct dvb_usb_adapter *adap)
{
	struct dvbsky_state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct i2c_adapter *i2c_adapter;
	struct m88ds3103_platform_data m88ds3103_pdata = {};
	struct ts2020_config ts2020_config = {};

	/* attach demod */
	m88ds3103_pdata.clk = 27000000;
	m88ds3103_pdata.i2c_wr_max = 33;
	m88ds3103_pdata.clk_out = 0;
	m88ds3103_pdata.ts_mode = M88DS3103_TS_CI;
	m88ds3103_pdata.ts_clk = 16000;
	m88ds3103_pdata.ts_clk_pol = 0;
	m88ds3103_pdata.agc = 0x99;
	m88ds3103_pdata.lnb_hv_pol = 1,
	m88ds3103_pdata.lnb_en_pol = 1,

	state->i2c_client_demod = dvb_module_probe("m88ds3103", NULL,
						   &d->i2c_adap,
						   0x68, &m88ds3103_pdata);
	if (!state->i2c_client_demod)
		return -ENODEV;

	adap->fe[0] = m88ds3103_pdata.get_dvb_frontend(state->i2c_client_demod);
	i2c_adapter = m88ds3103_pdata.get_i2c_adapter(state->i2c_client_demod);

	/* attach tuner */
	ts2020_config.fe = adap->fe[0];
	ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;

	state->i2c_client_tuner = dvb_module_probe("ts2020", NULL,
						   i2c_adapter,
						   0x60, &ts2020_config);
	if (!state->i2c_client_tuner) {
		dvb_module_release(state->i2c_client_demod);
		return -ENODEV;
	}

	/* delegate signal strength measurement to tuner */
	adap->fe[0]->ops.read_signal_strength =
			adap->fe[0]->ops.tuner_ops.get_rf_strength;

	/* hook fe: need to resync the slave fifo when signal locks. */
	state->fe_read_status = adap->fe[0]->ops.read_status;
	adap->fe[0]->ops.read_status = dvbsky_usb_read_status;

	/* hook fe: LNB off/on is control by Cypress usb chip. */
	state->fe_set_voltage = adap->fe[0]->ops.set_voltage;
	adap->fe[0]->ops.set_voltage = dvbsky_usb_set_voltage;

	return 0;
}