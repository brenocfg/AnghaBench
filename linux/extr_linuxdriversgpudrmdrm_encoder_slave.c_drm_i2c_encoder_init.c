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
struct module {int dummy; } ;
struct TYPE_4__ {TYPE_3__* driver; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct i2c_board_info {scalar_t__ platform_data; int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct drm_i2c_encoder_driver {int (* encoder_init ) (struct i2c_client*,struct drm_device*,struct drm_encoder_slave*) ;} ;
struct drm_encoder_slave {int /*<<< orphan*/  base; TYPE_2__* slave_funcs; struct i2c_client* bus_priv; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {struct module* owner; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_config ) (int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I2C_MODULE_PREFIX ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info const*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct i2c_client*,struct drm_device*,struct drm_encoder_slave*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,scalar_t__) ; 
 struct drm_i2c_encoder_driver* to_drm_i2c_encoder_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i2c_driver (TYPE_3__*) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 

int drm_i2c_encoder_init(struct drm_device *dev,
			 struct drm_encoder_slave *encoder,
			 struct i2c_adapter *adap,
			 const struct i2c_board_info *info)
{
	struct module *module = NULL;
	struct i2c_client *client;
	struct drm_i2c_encoder_driver *encoder_drv;
	int err = 0;

	request_module("%s%s", I2C_MODULE_PREFIX, info->type);

	client = i2c_new_device(adap, info);
	if (!client) {
		err = -ENOMEM;
		goto fail;
	}

	if (!client->dev.driver) {
		err = -ENODEV;
		goto fail_unregister;
	}

	module = client->dev.driver->owner;
	if (!try_module_get(module)) {
		err = -ENODEV;
		goto fail_unregister;
	}

	encoder->bus_priv = client;

	encoder_drv = to_drm_i2c_encoder_driver(to_i2c_driver(client->dev.driver));

	err = encoder_drv->encoder_init(client, dev, encoder);
	if (err)
		goto fail_unregister;

	if (info->platform_data)
		encoder->slave_funcs->set_config(&encoder->base,
						 info->platform_data);

	return 0;

fail_unregister:
	i2c_unregister_device(client);
	module_put(module);
fail:
	return err;
}