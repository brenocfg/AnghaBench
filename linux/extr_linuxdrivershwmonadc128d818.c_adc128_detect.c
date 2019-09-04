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
struct i2c_client {int /*<<< orphan*/  adapter; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC128_REG_BUSY_STATUS ; 
 int /*<<< orphan*/  ADC128_REG_CONFIG ; 
 int /*<<< orphan*/  ADC128_REG_CONFIG_ADV ; 
 int /*<<< orphan*/  ADC128_REG_CONV_RATE ; 
 int /*<<< orphan*/  ADC128_REG_DEV_ID ; 
 int /*<<< orphan*/  ADC128_REG_MAN_ID ; 
 int /*<<< orphan*/  ADC128_REG_ONESHOT ; 
 int /*<<< orphan*/  ADC128_REG_SHUTDOWN ; 
 int ENODEV ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adc128_detect(struct i2c_client *client, struct i2c_board_info *info)
{
	int man_id, dev_id;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		return -ENODEV;

	man_id = i2c_smbus_read_byte_data(client, ADC128_REG_MAN_ID);
	dev_id = i2c_smbus_read_byte_data(client, ADC128_REG_DEV_ID);
	if (man_id != 0x01 || dev_id != 0x09)
		return -ENODEV;

	/* Check unused bits for confirmation */
	if (i2c_smbus_read_byte_data(client, ADC128_REG_CONFIG) & 0xf4)
		return -ENODEV;
	if (i2c_smbus_read_byte_data(client, ADC128_REG_CONV_RATE) & 0xfe)
		return -ENODEV;
	if (i2c_smbus_read_byte_data(client, ADC128_REG_ONESHOT) & 0xfe)
		return -ENODEV;
	if (i2c_smbus_read_byte_data(client, ADC128_REG_SHUTDOWN) & 0xfe)
		return -ENODEV;
	if (i2c_smbus_read_byte_data(client, ADC128_REG_CONFIG_ADV) & 0xf8)
		return -ENODEV;
	if (i2c_smbus_read_byte_data(client, ADC128_REG_BUSY_STATUS) & 0xfc)
		return -ENODEV;

	strlcpy(info->type, "adc128d818", I2C_NAME_SIZE);

	return 0;
}