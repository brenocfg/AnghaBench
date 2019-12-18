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
struct pm860x_platform_data {scalar_t__ i2c_port; } ;
struct pm860x_chip {int buck3_double; int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ PI2C_PORT ; 
 int /*<<< orphan*/  PM8607_B0_MISC1 ; 
 int PM8607_B0_MISC1_PI2C ; 
 int /*<<< orphan*/  PM8607_BUCK3 ; 
 int PM8607_BUCK3_DOUBLE ; 
 int /*<<< orphan*/  PM8607_CHIP_ID ; 
 int PM8607_VERSION_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_codec_init (struct pm860x_chip*,struct pm860x_platform_data*) ; 
 int device_irq_init (struct pm860x_chip*,struct pm860x_platform_data*) ; 
 int /*<<< orphan*/  device_onkey_init (struct pm860x_chip*,struct pm860x_platform_data*) ; 
 int /*<<< orphan*/  device_power_init (struct pm860x_chip*,struct pm860x_platform_data*) ; 
 int /*<<< orphan*/  device_regulator_init (struct pm860x_chip*,struct pm860x_platform_data*) ; 
 int /*<<< orphan*/  device_rtc_init (struct pm860x_chip*,struct pm860x_platform_data*) ; 
 int /*<<< orphan*/  device_touch_init (struct pm860x_chip*,struct pm860x_platform_data*) ; 
 int pm860x_reg_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int pm860x_set_bits (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void device_8607_init(struct pm860x_chip *chip,
				       struct i2c_client *i2c,
				       struct pm860x_platform_data *pdata)
{
	int data, ret;

	ret = pm860x_reg_read(i2c, PM8607_CHIP_ID);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to read CHIP ID: %d\n", ret);
		goto out;
	}
	switch (ret & PM8607_VERSION_MASK) {
	case 0x40:
	case 0x50:
		dev_info(chip->dev, "Marvell 88PM8607 (ID: %02x) detected\n",
			 ret);
		break;
	default:
		dev_err(chip->dev,
			"Failed to detect Marvell 88PM8607. Chip ID: %02x\n",
			ret);
		goto out;
	}

	ret = pm860x_reg_read(i2c, PM8607_BUCK3);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to read BUCK3 register: %d\n", ret);
		goto out;
	}
	if (ret & PM8607_BUCK3_DOUBLE)
		chip->buck3_double = 1;

	ret = pm860x_reg_read(i2c, PM8607_B0_MISC1);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to read MISC1 register: %d\n", ret);
		goto out;
	}

	if (pdata && (pdata->i2c_port == PI2C_PORT))
		data = PM8607_B0_MISC1_PI2C;
	else
		data = 0;
	ret = pm860x_set_bits(i2c, PM8607_B0_MISC1, PM8607_B0_MISC1_PI2C, data);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to access MISC1:%d\n", ret);
		goto out;
	}

	ret = device_irq_init(chip, pdata);
	if (ret < 0)
		goto out;

	device_regulator_init(chip, pdata);
	device_rtc_init(chip, pdata);
	device_onkey_init(chip, pdata);
	device_touch_init(chip, pdata);
	device_power_init(chip, pdata);
	device_codec_init(chip, pdata);
out:
	return;
}