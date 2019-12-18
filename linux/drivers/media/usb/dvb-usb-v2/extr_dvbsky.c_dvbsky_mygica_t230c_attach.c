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
struct si2168_config {int ts_clock_inv; int if_port; int /*<<< orphan*/ * fe; int /*<<< orphan*/  ts_mode; struct i2c_adapter** i2c_adapter; } ;
struct si2157_config {int ts_clock_inv; int if_port; int /*<<< orphan*/ * fe; int /*<<< orphan*/  ts_mode; struct i2c_adapter** i2c_adapter; } ;
struct i2c_adapter {int dummy; } ;
struct dvbsky_state {void* i2c_client_demod; void* i2c_client_tuner; } ;
struct dvb_usb_device {TYPE_2__* udev; struct i2c_adapter i2c_adap; } ;
struct dvb_usb_adapter {int /*<<< orphan*/ ** fe; } ;
struct TYPE_3__ {int /*<<< orphan*/  idProduct; } ;
struct TYPE_4__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SI2168_TS_CLK_MANUAL ; 
 int /*<<< orphan*/  SI2168_TS_PARALLEL ; 
 scalar_t__ USB_PID_MYGICA_T230 ; 
 scalar_t__ USB_PID_MYGICA_T230C2 ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct dvbsky_state* adap_to_priv (struct dvb_usb_adapter*) ; 
 void* dvb_module_probe (char*,char*,struct i2c_adapter*,int,struct si2168_config*) ; 
 int /*<<< orphan*/  dvb_module_release (void*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvbsky_mygica_t230c_attach(struct dvb_usb_adapter *adap)
{
	struct dvbsky_state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct i2c_adapter *i2c_adapter;
	struct si2168_config si2168_config = {};
	struct si2157_config si2157_config = {};

	/* attach demod */
	si2168_config.i2c_adapter = &i2c_adapter;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_PARALLEL;
	if (le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_MYGICA_T230C2)
		si2168_config.ts_mode |= SI2168_TS_CLK_MANUAL;
	si2168_config.ts_clock_inv = 1;

	state->i2c_client_demod = dvb_module_probe("si2168", NULL,
						   &d->i2c_adap,
						   0x64, &si2168_config);
	if (!state->i2c_client_demod)
		return -ENODEV;

	/* attach tuner */
	si2157_config.fe = adap->fe[0];
	if (le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_MYGICA_T230) {
		si2157_config.if_port = 1;
		state->i2c_client_tuner = dvb_module_probe("si2157", NULL,
							   i2c_adapter,
							   0x60,
							   &si2157_config);
	} else {
		si2157_config.if_port = 0;
		state->i2c_client_tuner = dvb_module_probe("si2157", "si2141",
							   i2c_adapter,
							   0x60,
							   &si2157_config);
	}
	if (!state->i2c_client_tuner) {
		dvb_module_release(state->i2c_client_demod);
		return -ENODEV;
	}

	return 0;
}