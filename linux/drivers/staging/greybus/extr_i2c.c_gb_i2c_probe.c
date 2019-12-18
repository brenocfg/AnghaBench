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
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct i2c_adapter {int class; int /*<<< orphan*/  name; TYPE_2__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct gbphy_device_id {int dummy; } ;
struct gbphy_device {int /*<<< orphan*/  dev; TYPE_1__* cport_desc; int /*<<< orphan*/  bundle; } ;
struct gb_i2c_device {struct i2c_adapter adapter; struct gbphy_device* gbphy_dev; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_CLASS_HWMON ; 
 int I2C_CLASS_SPD ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct gb_connection* gb_connection_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct gb_i2c_device*) ; 
 int /*<<< orphan*/  gb_gbphy_set_data (struct gbphy_device*,struct gb_i2c_device*) ; 
 int /*<<< orphan*/  gb_i2c_algorithm ; 
 int gb_i2c_device_setup (struct gb_i2c_device*) ; 
 int /*<<< orphan*/  gbphy_runtime_put_autosuspend (struct gbphy_device*) ; 
 int i2c_add_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct gb_i2c_device*) ; 
 int /*<<< orphan*/  kfree (struct gb_i2c_device*) ; 
 struct gb_i2c_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int gb_i2c_probe(struct gbphy_device *gbphy_dev,
			const struct gbphy_device_id *id)
{
	struct gb_connection *connection;
	struct gb_i2c_device *gb_i2c_dev;
	struct i2c_adapter *adapter;
	int ret;

	gb_i2c_dev = kzalloc(sizeof(*gb_i2c_dev), GFP_KERNEL);
	if (!gb_i2c_dev)
		return -ENOMEM;

	connection =
		gb_connection_create(gbphy_dev->bundle,
				     le16_to_cpu(gbphy_dev->cport_desc->id),
				     NULL);
	if (IS_ERR(connection)) {
		ret = PTR_ERR(connection);
		goto exit_i2cdev_free;
	}

	gb_i2c_dev->connection = connection;
	gb_connection_set_data(connection, gb_i2c_dev);
	gb_i2c_dev->gbphy_dev = gbphy_dev;
	gb_gbphy_set_data(gbphy_dev, gb_i2c_dev);

	ret = gb_connection_enable(connection);
	if (ret)
		goto exit_connection_destroy;

	ret = gb_i2c_device_setup(gb_i2c_dev);
	if (ret)
		goto exit_connection_disable;

	/* Looks good; up our i2c adapter */
	adapter = &gb_i2c_dev->adapter;
	adapter->owner = THIS_MODULE;
	adapter->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	adapter->algo = &gb_i2c_algorithm;
	/* adapter->algo_data = what? */

	adapter->dev.parent = &gbphy_dev->dev;
	snprintf(adapter->name, sizeof(adapter->name), "Greybus i2c adapter");
	i2c_set_adapdata(adapter, gb_i2c_dev);

	ret = i2c_add_adapter(adapter);
	if (ret)
		goto exit_connection_disable;

	gbphy_runtime_put_autosuspend(gbphy_dev);
	return 0;

exit_connection_disable:
	gb_connection_disable(connection);
exit_connection_destroy:
	gb_connection_destroy(connection);
exit_i2cdev_free:
	kfree(gb_i2c_dev);

	return ret;
}