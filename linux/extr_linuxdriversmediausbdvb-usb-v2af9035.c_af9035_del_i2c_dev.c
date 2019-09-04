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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct state {struct i2c_client** i2c_client; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int AF9035_I2C_CLIENT_MAX ; 
 struct state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void af9035_del_i2c_dev(struct dvb_usb_device *d)
{
	int num;
	struct state *state = d_to_priv(d);
	struct usb_interface *intf = d->intf;
	struct i2c_client *client;

	/* find last used client */
	num = AF9035_I2C_CLIENT_MAX;
	while (num--) {
		if (state->i2c_client[num] != NULL)
			break;
	}

	dev_dbg(&intf->dev, "num=%d\n", num);

	if (num == -1) {
		dev_err(&intf->dev, "I2C client out of index\n");
		goto err;
	}

	client = state->i2c_client[num];

	/* decrease I2C driver usage count */
	module_put(client->dev.driver->owner);

	/* unregister I2C device */
	i2c_unregister_device(client);

	state->i2c_client[num] = NULL;
	return;
err:
	dev_dbg(&intf->dev, "failed\n");
}