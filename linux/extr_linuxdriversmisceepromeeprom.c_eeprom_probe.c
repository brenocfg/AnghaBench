#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {int addr; TYPE_1__ dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct eeprom_data {int /*<<< orphan*/  nature; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_BYTE_DATA ; 
 int /*<<< orphan*/  UNKNOWN ; 
 int /*<<< orphan*/  VAIO ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 struct eeprom_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeprom_attr ; 
 scalar_t__ i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct eeprom_data*) ; 
 char i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eeprom_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct eeprom_data *data;

	data = devm_kzalloc(&client->dev, sizeof(struct eeprom_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	memset(data->data, 0xff, EEPROM_SIZE);
	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	data->nature = UNKNOWN;

	/* Detect the Vaio nature of EEPROMs.
	   We use the "PCG-" or "VGN-" prefix as the signature. */
	if (client->addr == 0x57
	 && i2c_check_functionality(adapter, I2C_FUNC_SMBUS_READ_BYTE_DATA)) {
		char name[4];

		name[0] = i2c_smbus_read_byte_data(client, 0x80);
		name[1] = i2c_smbus_read_byte_data(client, 0x81);
		name[2] = i2c_smbus_read_byte_data(client, 0x82);
		name[3] = i2c_smbus_read_byte_data(client, 0x83);

		if (!memcmp(name, "PCG-", 4) || !memcmp(name, "VGN-", 4)) {
			dev_info(&client->dev, "Vaio EEPROM detected, "
				 "enabling privacy protection\n");
			data->nature = VAIO;
		}
	}

	/* create the sysfs eeprom file */
	return sysfs_create_bin_file(&client->dev.kobj, &eeprom_attr);
}