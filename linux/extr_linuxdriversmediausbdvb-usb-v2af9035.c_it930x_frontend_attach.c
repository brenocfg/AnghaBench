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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct state {struct i2c_adapter* i2c_adapter_demod; int /*<<< orphan*/  ops; TYPE_1__* af9033_config; } ;
struct si2168_config {int /*<<< orphan*/  ts_mode; int /*<<< orphan*/ ** fe; struct i2c_adapter** i2c_adapter; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; struct usb_interface* intf; } ;
struct dvb_usb_adapter {int id; int /*<<< orphan*/ ** fe; } ;
typedef  int /*<<< orphan*/  si2168_config ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/ ** fe; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SI2168_TS_SERIAL ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int af9035_add_i2c_dev (struct dvb_usb_device*,char*,int,struct si2168_config*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (struct si2168_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int it930x_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct usb_interface *intf = d->intf;
	int ret;
	struct si2168_config si2168_config;
	struct i2c_adapter *adapter;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	memset(&si2168_config, 0, sizeof(si2168_config));
	si2168_config.i2c_adapter = &adapter;
	si2168_config.fe = &adap->fe[0];
	si2168_config.ts_mode = SI2168_TS_SERIAL;

	state->af9033_config[adap->id].fe = &adap->fe[0];
	state->af9033_config[adap->id].ops = &state->ops;
	ret = af9035_add_i2c_dev(d, "si2168", 0x67, &si2168_config,
				&d->i2c_adap);
	if (ret)
		goto err;

	if (adap->fe[0] == NULL) {
		ret = -ENODEV;
		goto err;
	}
	state->i2c_adapter_demod = adapter;

	return 0;

err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);

	return ret;
}