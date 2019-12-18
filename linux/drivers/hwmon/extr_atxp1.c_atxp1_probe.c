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
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
struct atxp1_data {int vrm; int /*<<< orphan*/  update_lock; struct i2c_client* client; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  atxp1_groups ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct atxp1_data*,int /*<<< orphan*/ ) ; 
 struct atxp1_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int vid_which_vrm () ; 

__attribute__((used)) static int atxp1_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct atxp1_data *data;
	struct device *hwmon_dev;

	data = devm_kzalloc(dev, sizeof(struct atxp1_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	/* Get VRM */
	data->vrm = vid_which_vrm();
	if (data->vrm != 90 && data->vrm != 91) {
		dev_err(dev, "atxp1: Not supporting VRM %d.%d\n",
			data->vrm / 10, data->vrm % 10);
		return -ENODEV;
	}

	data->client = client;
	mutex_init(&data->update_lock);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, client->name,
							   data,
							   atxp1_groups);
	if (IS_ERR(hwmon_dev))
		return PTR_ERR(hwmon_dev);

	dev_info(dev, "Using VRM: %d.%d\n", data->vrm / 10, data->vrm % 10);

	return 0;
}