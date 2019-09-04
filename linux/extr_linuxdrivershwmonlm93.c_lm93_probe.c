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
struct lm93_data {void (* update ) (struct lm93_data*,struct i2c_client*) ;int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; struct device dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LM93_SMBUS_FUNC_FULL ; 
 int LM93_SMBUS_FUNC_MIN ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct lm93_data*,int /*<<< orphan*/ ) ; 
 struct lm93_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_block ; 
 int i2c_get_functionality (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm93_groups ; 
 int /*<<< orphan*/  lm93_init_client (struct i2c_client*) ; 
 void lm93_update_client_full (struct lm93_data*,struct i2c_client*) ; 
 void lm93_update_client_min (struct lm93_data*,struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm93_probe(struct i2c_client *client,
		      const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct lm93_data *data;
	struct device *hwmon_dev;
	int func;
	void (*update)(struct lm93_data *, struct i2c_client *);

	/* choose update routine based on bus capabilities */
	func = i2c_get_functionality(client->adapter);
	if (((LM93_SMBUS_FUNC_FULL & func) == LM93_SMBUS_FUNC_FULL) &&
			(!disable_block)) {
		dev_dbg(dev, "using SMBus block data transactions\n");
		update = lm93_update_client_full;
	} else if ((LM93_SMBUS_FUNC_MIN & func) == LM93_SMBUS_FUNC_MIN) {
		dev_dbg(dev, "disabled SMBus block data transactions\n");
		update = lm93_update_client_min;
	} else {
		dev_dbg(dev, "detect failed, smbus byte and/or word data not supported!\n");
		return -ENODEV;
	}

	data = devm_kzalloc(dev, sizeof(struct lm93_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	/* housekeeping */
	data->client = client;
	data->update = update;
	mutex_init(&data->update_lock);

	/* initialize the chip */
	lm93_init_client(client);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data,
							   lm93_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}