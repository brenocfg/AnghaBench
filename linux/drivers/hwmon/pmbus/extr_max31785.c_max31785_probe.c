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
struct pmbus_driver_info {int dummy; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; struct device dev; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 scalar_t__ MAX31785 ; 
 scalar_t__ MAX31785A ; 
 int /*<<< orphan*/  MFR_REVISION ; 
 int /*<<< orphan*/  PMBUS_PAGE ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct pmbus_driver_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 scalar_t__ i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ max31785_configure_dual_tach (struct i2c_client*,struct pmbus_driver_info*) ; 
 struct pmbus_driver_info max31785_info ; 
 int pmbus_do_probe (struct i2c_client*,struct i2c_device_id const*,struct pmbus_driver_info*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max31785_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct pmbus_driver_info *info;
	bool dual_tach = false;
	s64 ret;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		return -ENODEV;

	info = devm_kzalloc(dev, sizeof(struct pmbus_driver_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	*info = max31785_info;

	ret = i2c_smbus_write_byte_data(client, PMBUS_PAGE, 255);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_read_word_data(client, MFR_REVISION);
	if (ret < 0)
		return ret;

	if (ret == MAX31785A) {
		dual_tach = true;
	} else if (ret == MAX31785) {
		if (!strcmp("max31785a", id->name))
			dev_warn(dev, "Expected max3175a, found max31785: cannot provide secondary tachometer readings\n");
	} else {
		return -ENODEV;
	}

	if (dual_tach) {
		ret = max31785_configure_dual_tach(client, info);
		if (ret < 0)
			return ret;
	}

	return pmbus_do_probe(client, id, info);
}