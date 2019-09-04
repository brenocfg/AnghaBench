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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct dvb_usb_adapter {size_t id; } ;
struct af9015_state {struct i2c_client** demod_i2c_client; } ;

/* Variables and functions */
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct af9015_state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  dvb_module_release (struct i2c_client*) ; 

__attribute__((used)) static int af9015_frontend_detach(struct dvb_usb_adapter *adap)
{
	struct af9015_state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct usb_interface *intf = d->intf;
	struct i2c_client *client;

	dev_dbg(&intf->dev, "adap id %u\n", adap->id);

	/* Remove I2C demod */
	client = state->demod_i2c_client[adap->id];
	dvb_module_release(client);

	return 0;
}