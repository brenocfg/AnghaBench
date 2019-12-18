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
struct state {size_t it930x_addresses; int /*<<< orphan*/  i2c_adapter_demod; } ;
struct si2157_config {int /*<<< orphan*/  if_port; int /*<<< orphan*/  fe; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct dvb_usb_adapter {int id; int /*<<< orphan*/ * fe; } ;
typedef  int /*<<< orphan*/  si2157_config ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_i2c_addr; int /*<<< orphan*/  tuner_if_port; } ;

/* Variables and functions */
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int af9035_add_i2c_dev (struct dvb_usb_device*,char*,int /*<<< orphan*/ ,struct si2157_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__* it930x_addresses_table ; 
 int /*<<< orphan*/  memset (struct si2157_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int it930x_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct usb_interface *intf = d->intf;
	int ret;
	struct si2157_config si2157_config;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	memset(&si2157_config, 0, sizeof(si2157_config));
	si2157_config.fe = adap->fe[0];
	si2157_config.if_port = it930x_addresses_table[state->it930x_addresses].tuner_if_port;
	ret = af9035_add_i2c_dev(d, "si2157",
				 it930x_addresses_table[state->it930x_addresses].tuner_i2c_addr,
				 &si2157_config, state->i2c_adapter_demod);
	if (ret)
		goto err;

	return 0;

err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);

	return ret;
}