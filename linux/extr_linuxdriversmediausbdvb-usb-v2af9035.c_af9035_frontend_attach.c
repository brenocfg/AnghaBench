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
struct state {TYPE_3__* af9033_config; int /*<<< orphan*/ * af9033_i2c_addr; int /*<<< orphan*/  ops; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; struct usb_interface* intf; } ;
struct dvb_usb_adapter {int id; TYPE_2__** fe; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; TYPE_2__** fe; int /*<<< orphan*/  tuner; } ;
struct TYPE_4__ {int /*<<< orphan*/ * i2c_gate_ctrl; } ;
struct TYPE_5__ {int /*<<< orphan*/  callback; TYPE_1__ ops; } ;

/* Variables and functions */
 int ENODEV ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int af9035_add_i2c_dev (struct dvb_usb_device*,char*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  af9035_frontend_callback ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int af9035_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct usb_interface *intf = d->intf;
	int ret;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	if (!state->af9033_config[adap->id].tuner) {
		/* unsupported tuner */
		ret = -ENODEV;
		goto err;
	}

	state->af9033_config[adap->id].fe = &adap->fe[0];
	state->af9033_config[adap->id].ops = &state->ops;
	ret = af9035_add_i2c_dev(d, "af9033", state->af9033_i2c_addr[adap->id],
			&state->af9033_config[adap->id], &d->i2c_adap);
	if (ret)
		goto err;

	if (adap->fe[0] == NULL) {
		ret = -ENODEV;
		goto err;
	}

	/* disable I2C-gate */
	adap->fe[0]->ops.i2c_gate_ctrl = NULL;
	adap->fe[0]->callback = af9035_frontend_callback;

	return 0;

err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);

	return ret;
}