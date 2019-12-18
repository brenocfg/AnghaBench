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
struct TYPE_4__ {TYPE_1__* driver; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  request_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct i2c_client *smi_add_i2c_client(struct i2c_adapter *adapter,
			struct i2c_board_info *info)
{
	struct i2c_client *client;

	request_module(info->type);
	client = i2c_new_device(adapter, info);
	if (client == NULL || client->dev.driver == NULL)
		goto err_add_i2c_client;

	if (!try_module_get(client->dev.driver->owner)) {
		i2c_unregister_device(client);
		goto err_add_i2c_client;
	}
	return client;

err_add_i2c_client:
	client = NULL;
	return client;
}