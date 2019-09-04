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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct i2c_client {int addr; int /*<<< orphan*/  name; } ;
struct i2c_board_info {struct htcpld_chip* platform_data; int /*<<< orphan*/  type; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct htcpld_data {struct htcpld_chip* chip; } ;
struct htcpld_core_platform_data {int /*<<< orphan*/  i2c_adapter_id; struct htcpld_chip_platform_data* chip; } ;
struct htcpld_chip_platform_data {int /*<<< orphan*/  addr; } ;
struct htcpld_chip {int /*<<< orphan*/  cache_out; int /*<<< orphan*/  cache_in; struct i2c_client* client; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 struct htcpld_core_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  htcpld_chip_reset (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 struct i2c_adapter* i2c_get_adapter (int /*<<< orphan*/ ) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct htcpld_chip*) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 struct htcpld_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int htcpld_register_chip_i2c(
		struct platform_device *pdev,
		int chip_index)
{
	struct htcpld_data *htcpld;
	struct device *dev = &pdev->dev;
	struct htcpld_core_platform_data *pdata;
	struct htcpld_chip *chip;
	struct htcpld_chip_platform_data *plat_chip_data;
	struct i2c_adapter *adapter;
	struct i2c_client *client;
	struct i2c_board_info info;

	/* Get the platform and driver data */
	pdata = dev_get_platdata(dev);
	htcpld = platform_get_drvdata(pdev);
	chip = &htcpld->chip[chip_index];
	plat_chip_data = &pdata->chip[chip_index];

	adapter = i2c_get_adapter(pdata->i2c_adapter_id);
	if (!adapter) {
		/* Eek, no such I2C adapter!  Bail out. */
		dev_warn(dev, "Chip at i2c address 0x%x: Invalid i2c adapter %d\n",
			 plat_chip_data->addr, pdata->i2c_adapter_id);
		return -ENODEV;
	}

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_READ_BYTE_DATA)) {
		dev_warn(dev, "i2c adapter %d non-functional\n",
			 pdata->i2c_adapter_id);
		return -EINVAL;
	}

	memset(&info, 0, sizeof(struct i2c_board_info));
	info.addr = plat_chip_data->addr;
	strlcpy(info.type, "htcpld-chip", I2C_NAME_SIZE);
	info.platform_data = chip;

	/* Add the I2C device.  This calls the probe() function. */
	client = i2c_new_device(adapter, &info);
	if (!client) {
		/* I2C device registration failed, contineu with the next */
		dev_warn(dev, "Unable to add I2C device for 0x%x\n",
			 plat_chip_data->addr);
		return -ENODEV;
	}

	i2c_set_clientdata(client, chip);
	snprintf(client->name, I2C_NAME_SIZE, "Chip_0x%x", client->addr);
	chip->client = client;

	/* Reset the chip */
	htcpld_chip_reset(client);
	chip->cache_in = i2c_smbus_read_byte_data(client, chip->cache_out);

	return 0;
}