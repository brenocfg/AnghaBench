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
typedef  int u8 ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; } ;
struct fts_data {struct i2c_client* client; int /*<<< orphan*/  access_lock; int /*<<< orphan*/  update_lock; } ;
struct device {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FTS_DEVICE_ID_REG ; 
 int /*<<< orphan*/  FTS_DEVICE_REVISION_REG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct fts_data*) ; 
 struct device* devm_hwmon_device_register_with_groups (int /*<<< orphan*/ *,char*,struct fts_data*,int /*<<< orphan*/ ) ; 
 struct fts_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts_attr_groups ; 
 int fts_watchdog_init (struct fts_data*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	u8 revision;
	struct fts_data *data;
	int err;
	s8 deviceid;
	struct device *hwmon_dev;

	if (client->addr != 0x73)
		return -ENODEV;

	/* Baseboard Management Controller check */
	deviceid = i2c_smbus_read_byte_data(client, FTS_DEVICE_ID_REG);
	if (deviceid > 0 && (deviceid & 0xF0) == 0x10) {
		switch (deviceid & 0x0F) {
		case 0x01:
			break;
		default:
			dev_dbg(&client->dev,
				"No Baseboard Management Controller\n");
			return -ENODEV;
		}
	} else {
		dev_dbg(&client->dev, "No fujitsu board\n");
		return -ENODEV;
	}

	data = devm_kzalloc(&client->dev, sizeof(struct fts_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	mutex_init(&data->update_lock);
	mutex_init(&data->access_lock);
	data->client = client;
	dev_set_drvdata(&client->dev, data);

	err = i2c_smbus_read_byte_data(client, FTS_DEVICE_REVISION_REG);
	if (err < 0)
		return err;
	revision = err;

	hwmon_dev = devm_hwmon_device_register_with_groups(&client->dev,
							   "ftsteutates",
							   data,
							   fts_attr_groups);
	if (IS_ERR(hwmon_dev))
		return PTR_ERR(hwmon_dev);

	err = fts_watchdog_init(data);
	if (err)
		return err;

	dev_info(&client->dev, "Detected FTS Teutates chip, revision: %d.%d\n",
		 (revision & 0xF0) >> 4, revision & 0x0F);
	return 0;
}