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
struct sp2_config {int if_port; int /*<<< orphan*/  ci_control; struct dvb_usb_device* priv; int /*<<< orphan*/ * dvb_adap; int /*<<< orphan*/ * fe; int /*<<< orphan*/  ts_mode; struct i2c_adapter** i2c_adapter; } ;
struct si2168_config {int if_port; int /*<<< orphan*/  ci_control; struct dvb_usb_device* priv; int /*<<< orphan*/ * dvb_adap; int /*<<< orphan*/ * fe; int /*<<< orphan*/  ts_mode; struct i2c_adapter** i2c_adapter; } ;
struct si2157_config {int if_port; int /*<<< orphan*/  ci_control; struct dvb_usb_device* priv; int /*<<< orphan*/ * dvb_adap; int /*<<< orphan*/ * fe; int /*<<< orphan*/  ts_mode; struct i2c_adapter** i2c_adapter; } ;
struct i2c_adapter {int dummy; } ;
struct dvbsky_state {void* i2c_client_demod; void* i2c_client_tuner; void* i2c_client_ci; } ;
struct dvb_usb_device {struct i2c_adapter i2c_adap; } ;
struct dvb_usb_adapter {int /*<<< orphan*/  dvb_adap; int /*<<< orphan*/ ** fe; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SI2168_TS_PARALLEL ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct dvbsky_state* adap_to_priv (struct dvb_usb_adapter*) ; 
 void* dvb_module_probe (char*,int /*<<< orphan*/ *,struct i2c_adapter*,int,struct sp2_config*) ; 
 int /*<<< orphan*/  dvb_module_release (void*) ; 
 int /*<<< orphan*/  dvbsky_ci_ctrl ; 

__attribute__((used)) static int dvbsky_t680c_attach(struct dvb_usb_adapter *adap)
{
	struct dvbsky_state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct i2c_adapter *i2c_adapter;
	struct si2168_config si2168_config = {};
	struct si2157_config si2157_config = {};
	struct sp2_config sp2_config = {};

	/* attach demod */
	si2168_config.i2c_adapter = &i2c_adapter;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_PARALLEL;

	state->i2c_client_demod = dvb_module_probe("si2168", NULL,
						   &d->i2c_adap,
						   0x64, &si2168_config);
	if (!state->i2c_client_demod)
		return -ENODEV;

	/* attach tuner */
	si2157_config.fe = adap->fe[0];
	si2157_config.if_port = 1;

	state->i2c_client_tuner = dvb_module_probe("si2157", NULL,
						   i2c_adapter,
						   0x60, &si2157_config);
	if (!state->i2c_client_tuner) {
		dvb_module_release(state->i2c_client_demod);
		return -ENODEV;
	}

	/* attach ci controller */
	sp2_config.dvb_adap = &adap->dvb_adap;
	sp2_config.priv = d;
	sp2_config.ci_control = dvbsky_ci_ctrl;

	state->i2c_client_ci = dvb_module_probe("sp2", NULL,
						&d->i2c_adap,
						0x40, &sp2_config);

	if (!state->i2c_client_ci) {
		dvb_module_release(state->i2c_client_tuner);
		dvb_module_release(state->i2c_client_demod);
		return -ENODEV;
	}

	return 0;
}