#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ts2020_config {int clk; int i2c_wr_max; int ts_clk; int agc; int lnb_hv_pol; TYPE_6__* fe; struct i2c_adapter* (* get_i2c_adapter ) (struct i2c_client*) ;TYPE_6__* (* get_dvb_frontend ) (struct i2c_client*) ;scalar_t__ lnb_en_pol; scalar_t__ envelope_mode; int /*<<< orphan*/  clk_out; scalar_t__ agc_inv; scalar_t__ spec_inv; scalar_t__ ts_clk_pol; int /*<<< orphan*/  ts_mode; } ;
struct m88ds3103_platform_data {int clk; int i2c_wr_max; int ts_clk; int agc; int lnb_hv_pol; TYPE_6__* fe; struct i2c_adapter* (* get_i2c_adapter ) (struct i2c_client*) ;TYPE_6__* (* get_dvb_frontend ) (struct i2c_client*) ;scalar_t__ lnb_en_pol; scalar_t__ envelope_mode; int /*<<< orphan*/  clk_out; scalar_t__ agc_inv; scalar_t__ spec_inv; scalar_t__ ts_clk_pol; int /*<<< orphan*/  ts_mode; } ;
struct TYPE_11__ {TYPE_3__* driver; } ;
struct i2c_client {TYPE_4__ dev; } ;
struct i2c_board_info {int addr; struct ts2020_config* platform_data; int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct dw2102_state {int* data; scalar_t__ last_lock; int /*<<< orphan*/  fe_read_status; struct i2c_client* i2c_client_tuner; struct i2c_client* i2c_client_demod; } ;
struct dvb_usb_device {struct i2c_adapter i2c_adap; int /*<<< orphan*/  data_mutex; struct dw2102_state* priv; } ;
struct dvb_usb_adapter {TYPE_5__* fe_adap; struct dvb_usb_device* dev; } ;
typedef  int /*<<< orphan*/  board_info ;
struct TYPE_8__ {int /*<<< orphan*/  get_rf_strength; } ;
struct TYPE_9__ {int /*<<< orphan*/  read_status; TYPE_1__ tuner_ops; int /*<<< orphan*/  read_signal_strength; } ;
struct TYPE_13__ {TYPE_2__ ops; } ;
struct TYPE_12__ {TYPE_6__* fe; } ;
struct TYPE_10__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  M88DS3103_CLOCK_OUT_ENABLED ; 
 int /*<<< orphan*/  M88DS3103_TS_CI ; 
 int /*<<< orphan*/  dvb_frontend_detach (TYPE_6__*) ; 
 scalar_t__ dvb_usb_generic_rw (struct dvb_usb_device*,int*,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_module (char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_6__* stub1 (struct i2c_client*) ; 
 struct i2c_adapter* stub2 (struct i2c_client*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_s2_4600_read_status ; 

__attribute__((used)) static int tt_s2_4600_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *d = adap->dev;
	struct dw2102_state *state = d->priv;
	struct i2c_adapter *i2c_adapter;
	struct i2c_client *client;
	struct i2c_board_info board_info;
	struct m88ds3103_platform_data m88ds3103_pdata = {};
	struct ts2020_config ts2020_config = {};

	mutex_lock(&d->data_mutex);

	state->data[0] = 0xe;
	state->data[1] = 0x80;
	state->data[2] = 0x0;

	if (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0xe;
	state->data[1] = 0x02;
	state->data[2] = 1;

	if (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");
	msleep(300);

	state->data[0] = 0xe;
	state->data[1] = 0x83;
	state->data[2] = 0;

	if (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0xe;
	state->data[1] = 0x83;
	state->data[2] = 1;

	if (dvb_usb_generic_rw(d, state->data, 3, state->data, 1, 0) < 0)
		err("command 0x0e transfer failed.");

	state->data[0] = 0x51;

	if (dvb_usb_generic_rw(d, state->data, 1, state->data, 1, 0) < 0)
		err("command 0x51 transfer failed.");

	mutex_unlock(&d->data_mutex);

	/* attach demod */
	m88ds3103_pdata.clk = 27000000;
	m88ds3103_pdata.i2c_wr_max = 33;
	m88ds3103_pdata.ts_mode = M88DS3103_TS_CI;
	m88ds3103_pdata.ts_clk = 16000;
	m88ds3103_pdata.ts_clk_pol = 0;
	m88ds3103_pdata.spec_inv = 0;
	m88ds3103_pdata.agc = 0x99;
	m88ds3103_pdata.agc_inv = 0;
	m88ds3103_pdata.clk_out = M88DS3103_CLOCK_OUT_ENABLED;
	m88ds3103_pdata.envelope_mode = 0;
	m88ds3103_pdata.lnb_hv_pol = 1;
	m88ds3103_pdata.lnb_en_pol = 0;
	memset(&board_info, 0, sizeof(board_info));
	strscpy(board_info.type, "m88ds3103", I2C_NAME_SIZE);
	board_info.addr = 0x68;
	board_info.platform_data = &m88ds3103_pdata;
	request_module("m88ds3103");
	client = i2c_new_device(&d->i2c_adap, &board_info);
	if (client == NULL || client->dev.driver == NULL)
		return -ENODEV;
	if (!try_module_get(client->dev.driver->owner)) {
		i2c_unregister_device(client);
		return -ENODEV;
	}
	adap->fe_adap[0].fe = m88ds3103_pdata.get_dvb_frontend(client);
	i2c_adapter = m88ds3103_pdata.get_i2c_adapter(client);

	state->i2c_client_demod = client;

	/* attach tuner */
	ts2020_config.fe = adap->fe_adap[0].fe;
	memset(&board_info, 0, sizeof(board_info));
	strscpy(board_info.type, "ts2022", I2C_NAME_SIZE);
	board_info.addr = 0x60;
	board_info.platform_data = &ts2020_config;
	request_module("ts2020");
	client = i2c_new_device(i2c_adapter, &board_info);

	if (client == NULL || client->dev.driver == NULL) {
		dvb_frontend_detach(adap->fe_adap[0].fe);
		return -ENODEV;
	}

	if (!try_module_get(client->dev.driver->owner)) {
		i2c_unregister_device(client);
		dvb_frontend_detach(adap->fe_adap[0].fe);
		return -ENODEV;
	}

	/* delegate signal strength measurement to tuner */
	adap->fe_adap[0].fe->ops.read_signal_strength =
			adap->fe_adap[0].fe->ops.tuner_ops.get_rf_strength;

	state->i2c_client_tuner = client;

	/* hook fe: need to resync the slave fifo when signal locks */
	state->fe_read_status = adap->fe_adap[0].fe->ops.read_status;
	adap->fe_adap[0].fe->ops.read_status = tt_s2_4600_read_status;

	state->last_lock = 0;

	return 0;
}