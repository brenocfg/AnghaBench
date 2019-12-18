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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_device_id {scalar_t__ driver_data; int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_BLOCK_DATA ; 
 int I2C_SMBUS_BLOCK_MAX ; 
 int LTC2974_ID ; 
 int LTC2975_ID ; 
 int LTC2977_ID ; 
 int LTC2978_ID_MASK ; 
 int LTC2978_ID_REV1 ; 
 int LTC2978_ID_REV2 ; 
 int /*<<< orphan*/  LTC2978_MFR_SPECIAL_ID ; 
 int LTC2980_ID_A ; 
 int LTC2980_ID_B ; 
 int LTC3880_ID ; 
 int LTC3882_ID ; 
 int LTC3882_ID_D1 ; 
 int LTC3883_ID ; 
 int LTC3886_ID ; 
 int LTC3887_ID ; 
 int LTM2987_ID_A ; 
 int LTM2987_ID_B ; 
 int LTM4675_ID ; 
 int LTM4676A_ID ; 
 int LTM4676_ID_REV1 ; 
 int LTM4676_ID_REV2 ; 
 int LTM4686_ID ; 
 int /*<<< orphan*/  PMBUS_MFR_ID ; 
 int /*<<< orphan*/  PMBUS_MFR_MODEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_block_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int ltc2974 ; 
 int ltc2975 ; 
 int ltc2977 ; 
 int ltc2978 ; 
 struct i2c_device_id* ltc2978_id ; 
 int ltc2980 ; 
 int ltc3880 ; 
 int ltc3882 ; 
 int ltc3883 ; 
 int ltc3886 ; 
 int ltc3887 ; 
 int ltm2987 ; 
 int ltm4675 ; 
 int ltm4676 ; 
 int ltm4686 ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int ltc2978_get_id(struct i2c_client *client)
{
	int chip_id;

	chip_id = i2c_smbus_read_word_data(client, LTC2978_MFR_SPECIAL_ID);
	if (chip_id < 0) {
		const struct i2c_device_id *id;
		u8 buf[I2C_SMBUS_BLOCK_MAX];
		int ret;

		if (!i2c_check_functionality(client->adapter,
					     I2C_FUNC_SMBUS_READ_BLOCK_DATA))
			return -ENODEV;

		ret = i2c_smbus_read_block_data(client, PMBUS_MFR_ID, buf);
		if (ret < 0)
			return ret;
		if (ret < 3 || strncmp(buf, "LTC", 3))
			return -ENODEV;

		ret = i2c_smbus_read_block_data(client, PMBUS_MFR_MODEL, buf);
		if (ret < 0)
			return ret;
		for (id = &ltc2978_id[0]; strlen(id->name); id++) {
			if (!strncasecmp(id->name, buf, strlen(id->name)))
				return (int)id->driver_data;
		}
		return -ENODEV;
	}

	chip_id &= LTC2978_ID_MASK;

	if (chip_id == LTC2974_ID)
		return ltc2974;
	else if (chip_id == LTC2975_ID)
		return ltc2975;
	else if (chip_id == LTC2977_ID)
		return ltc2977;
	else if (chip_id == LTC2978_ID_REV1 || chip_id == LTC2978_ID_REV2)
		return ltc2978;
	else if (chip_id == LTC2980_ID_A || chip_id == LTC2980_ID_B)
		return ltc2980;
	else if (chip_id == LTC3880_ID)
		return ltc3880;
	else if (chip_id == LTC3882_ID || chip_id == LTC3882_ID_D1)
		return ltc3882;
	else if (chip_id == LTC3883_ID)
		return ltc3883;
	else if (chip_id == LTC3886_ID)
		return ltc3886;
	else if (chip_id == LTC3887_ID)
		return ltc3887;
	else if (chip_id == LTM2987_ID_A || chip_id == LTM2987_ID_B)
		return ltm2987;
	else if (chip_id == LTM4675_ID)
		return ltm4675;
	else if (chip_id == LTM4676_ID_REV1 || chip_id == LTM4676_ID_REV2 ||
		 chip_id == LTM4676A_ID)
		return ltm4676;
	else if (chip_id == LTM4686_ID)
		return ltm4686;

	dev_err(&client->dev, "Unsupported chip ID 0x%x\n", chip_id);
	return -ENODEV;
}