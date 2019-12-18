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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; struct usb_interface* intf; } ;
struct dvb_usb_adapter {int id; TYPE_2__** fe; } ;
struct af9015_state {int /*<<< orphan*/ * sleep; int /*<<< orphan*/ * init; int /*<<< orphan*/ * read_status; int /*<<< orphan*/ * set_frontend; struct i2c_client** demod_i2c_client; TYPE_3__* af9013_pdata; int /*<<< orphan*/ * af9013_i2c_addr; scalar_t__ dual_mode; } ;
struct TYPE_6__ {int ts_output_pin; TYPE_2__* (* get_dvb_frontend ) (struct i2c_client*) ;void** gpio; int /*<<< orphan*/  api_version; int /*<<< orphan*/  ts_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  sleep; int /*<<< orphan*/  init; int /*<<< orphan*/  read_status; int /*<<< orphan*/  set_frontend; } ;
struct TYPE_5__ {TYPE_1__ ops; } ;

/* Variables and functions */
 void* AF9013_GPIO_HI ; 
 void* AF9013_GPIO_LO ; 
 void* AF9013_GPIO_TUNER_ON ; 
 int /*<<< orphan*/  AF9013_TS_MODE_SERIAL ; 
 int /*<<< orphan*/  AF9013_TS_MODE_USB ; 
 int ENODEV ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct af9015_state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  af9015_af9013_init ; 
 int /*<<< orphan*/  af9015_af9013_read_status ; 
 int /*<<< orphan*/  af9015_af9013_set_frontend ; 
 int /*<<< orphan*/  af9015_af9013_sleep ; 
 int af9015_copy_firmware (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct i2c_client* dvb_module_probe (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_2__* stub1 (struct i2c_client*) ; 

__attribute__((used)) static int af9015_af9013_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct af9015_state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct usb_interface *intf = d->intf;
	struct i2c_client *client;
	int ret;

	dev_dbg(&intf->dev, "adap id %u\n", adap->id);

	if (adap->id == 0) {
		state->af9013_pdata[0].ts_mode = AF9013_TS_MODE_USB;
		memcpy(state->af9013_pdata[0].api_version, "\x0\x1\x9\x0", 4);
		state->af9013_pdata[0].gpio[0] = AF9013_GPIO_HI;
		state->af9013_pdata[0].gpio[3] = AF9013_GPIO_TUNER_ON;
	} else if (adap->id == 1) {
		state->af9013_pdata[1].ts_mode = AF9013_TS_MODE_SERIAL;
		state->af9013_pdata[1].ts_output_pin = 7;
		memcpy(state->af9013_pdata[1].api_version, "\x0\x1\x9\x0", 4);
		state->af9013_pdata[1].gpio[0] = AF9013_GPIO_TUNER_ON;
		state->af9013_pdata[1].gpio[1] = AF9013_GPIO_LO;

		/* copy firmware to 2nd demodulator */
		if (state->dual_mode) {
			/* Wait 2nd demodulator ready */
			msleep(100);

			ret = af9015_copy_firmware(adap_to_d(adap));
			if (ret) {
				dev_err(&intf->dev,
					"firmware copy to 2nd frontend failed, will disable it\n");
				state->dual_mode = 0;
				goto err;
			}
		} else {
			ret = -ENODEV;
			goto err;
		}
	}

	/* Add I2C demod */
	client = dvb_module_probe("af9013", NULL, &d->i2c_adap,
				  state->af9013_i2c_addr[adap->id],
				  &state->af9013_pdata[adap->id]);
	if (!client) {
		ret = -ENODEV;
		goto err;
	}
	adap->fe[0] = state->af9013_pdata[adap->id].get_dvb_frontend(client);
	state->demod_i2c_client[adap->id] = client;

	/*
	 * AF9015 firmware does not like if it gets interrupted by I2C adapter
	 * request on some critical phases. During normal operation I2C adapter
	 * is used only 2nd demodulator and tuner on dual tuner devices.
	 * Override demodulator callbacks and use mutex for limit access to
	 * those "critical" paths to keep AF9015 happy.
	 */
	if (adap->fe[0]) {
		state->set_frontend[adap->id] = adap->fe[0]->ops.set_frontend;
		adap->fe[0]->ops.set_frontend = af9015_af9013_set_frontend;
		state->read_status[adap->id] = adap->fe[0]->ops.read_status;
		adap->fe[0]->ops.read_status = af9015_af9013_read_status;
		state->init[adap->id] = adap->fe[0]->ops.init;
		adap->fe[0]->ops.init = af9015_af9013_init;
		state->sleep[adap->id] = adap->fe[0]->ops.sleep;
		adap->fe[0]->ops.sleep = af9015_af9013_sleep;
	}

	return 0;
err:
	dev_dbg(&intf->dev, "failed %d\n", ret);
	return ret;
}