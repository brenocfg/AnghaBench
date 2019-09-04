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
struct usb_interface {int dummy; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct dw2102_state {struct i2c_client* i2c_client_demod; struct i2c_client* i2c_client_tuner; } ;
struct dvb_usb_device {scalar_t__ priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_usb_device_exit (struct usb_interface*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct dvb_usb_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void dw2102_disconnect(struct usb_interface *intf)
{
	struct dvb_usb_device *d = usb_get_intfdata(intf);
	struct dw2102_state *st = (struct dw2102_state *)d->priv;
	struct i2c_client *client;

	/* remove I2C client for tuner */
	client = st->i2c_client_tuner;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}

	/* remove I2C client for demodulator */
	client = st->i2c_client_demod;
	if (client) {
		module_put(client->dev.driver->owner);
		i2c_unregister_device(client);
	}

	dvb_usb_device_exit(intf);
}