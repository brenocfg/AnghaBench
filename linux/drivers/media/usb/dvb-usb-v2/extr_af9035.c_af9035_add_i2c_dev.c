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
typedef  int /*<<< orphan*/  u8 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct state {struct i2c_client** i2c_client; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct i2c_board_info {void* platform_data; int /*<<< orphan*/  type; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int AF9035_I2C_CLIENT_MAX ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 struct state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int af9035_add_i2c_dev(struct dvb_usb_device *d, const char *type,
		u8 addr, void *platform_data, struct i2c_adapter *adapter)
{
	int ret, num;
	struct state *state = d_to_priv(d);
	struct usb_interface *intf = d->intf;
	struct i2c_client *client;
	struct i2c_board_info board_info = {
		.addr = addr,
		.platform_data = platform_data,
	};

	strscpy(board_info.type, type, I2C_NAME_SIZE);

	/* find first free client */
	for (num = 0; num < AF9035_I2C_CLIENT_MAX; num++) {
		if (state->i2c_client[num] == NULL)
			break;
	}

	dev_dbg(&intf->dev, "num=%d\n", num);

	if (num == AF9035_I2C_CLIENT_MAX) {
		dev_err(&intf->dev, "I2C client out of index\n");
		ret = -ENODEV;
		goto err;
	}

	request_module("%s", board_info.type);

	/* register I2C device */
	client = i2c_new_device(adapter, &board_info);
	if (client == NULL || client->dev.driver == NULL) {
		ret = -ENODEV;
		goto err;
	}

	/* increase I2C driver usage count */
	if (!try_module_get(client->dev.driver->owner)) {
		i2c_unregister_device(client);
		ret = -ENODEV;
		goto err;
	}

	state->i2c_client[num] = client;
	return 0;
err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);
	return ret;
}