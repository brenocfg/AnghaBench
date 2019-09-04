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
struct pmbus_platform_data {int /*<<< orphan*/  flags; } ;
struct pmbus_driver_info {int /*<<< orphan*/  identify; int /*<<< orphan*/  pages; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; int /*<<< orphan*/  name; } ;
struct device {struct pmbus_platform_data* platform_data; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PMBUS_SKIP_STATUS_CHECK ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int pmbus_do_probe (struct i2c_client*,struct i2c_device_id const*,struct pmbus_driver_info*) ; 
 int /*<<< orphan*/  pmbus_identify ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pmbus_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct pmbus_driver_info *info;
	struct pmbus_platform_data *pdata = NULL;
	struct device *dev = &client->dev;

	info = devm_kzalloc(dev, sizeof(struct pmbus_driver_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	if (!strcmp(id->name, "dps460") || !strcmp(id->name, "dps800") ||
	    !strcmp(id->name, "sgd009")) {
		pdata = devm_kzalloc(dev, sizeof(struct pmbus_platform_data),
				     GFP_KERNEL);
		if (!pdata)
			return -ENOMEM;

		pdata->flags = PMBUS_SKIP_STATUS_CHECK;
	}

	info->pages = id->driver_data;
	info->identify = pmbus_identify;
	dev->platform_data = pdata;

	return pmbus_do_probe(client, id, info);
}