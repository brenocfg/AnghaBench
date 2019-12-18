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
struct smsc47m192_data {int /*<<< orphan*/ ** groups; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  vrm; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  SMSC47M192_REG_CONFIG ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct smsc47m192_data*,int /*<<< orphan*/ **) ; 
 struct smsc47m192_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsc47m192_group ; 
 int /*<<< orphan*/  smsc47m192_group_in4 ; 
 int /*<<< orphan*/  smsc47m192_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static int smsc47m192_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct device *hwmon_dev;
	struct smsc47m192_data *data;
	int config;

	data = devm_kzalloc(dev, sizeof(struct smsc47m192_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->client = client;
	data->vrm = vid_which_vrm();
	mutex_init(&data->update_lock);

	/* Initialize the SMSC47M192 chip */
	smsc47m192_init_client(client);

	/* sysfs hooks */
	data->groups[0] = &smsc47m192_group;
	/* Pin 110 is either in4 (+12V) or VID4 */
	config = i2c_smbus_read_byte_data(client, SMSC47M192_REG_CONFIG);
	if (!(config & 0x20))
		data->groups[1] = &smsc47m192_group_in4;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}