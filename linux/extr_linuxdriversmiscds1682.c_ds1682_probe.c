#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ds1682_eeprom_attr ; 
 int /*<<< orphan*/  ds1682_group ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds1682_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int rc;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_I2C_BLOCK)) {
		dev_err(&client->dev, "i2c bus does not support the ds1682\n");
		rc = -ENODEV;
		goto exit;
	}

	rc = sysfs_create_group(&client->dev.kobj, &ds1682_group);
	if (rc)
		goto exit;

	rc = sysfs_create_bin_file(&client->dev.kobj, &ds1682_eeprom_attr);
	if (rc)
		goto exit_bin_attr;

	return 0;

 exit_bin_attr:
	sysfs_remove_group(&client->dev.kobj, &ds1682_group);
 exit:
	return rc;
}