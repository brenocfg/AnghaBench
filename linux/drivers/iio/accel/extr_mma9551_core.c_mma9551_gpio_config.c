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
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  enum mma9551_gpio_pin { ____Placeholder_mma9551_gpio_pin } mma9551_gpio_pin ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MMA9551_APPID_GPIO ; 
 int MMA9551_GPIO_POL_LSB ; 
 int MMA9551_GPIO_POL_MSB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
#define  mma9551_gpio6 131 
#define  mma9551_gpio7 130 
#define  mma9551_gpio8 129 
#define  mma9551_gpio9 128 
 int mma9551_gpio_max ; 
 int mma9551_update_config_bits (struct i2c_client*,int /*<<< orphan*/ ,int,int,int) ; 
 int mma9551_write_config_byte (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 

int mma9551_gpio_config(struct i2c_client *client, enum mma9551_gpio_pin pin,
			u8 app_id, u8 bitnum, int polarity)
{
	u8 reg, pol_mask, pol_val;
	int ret;

	if (pin > mma9551_gpio_max) {
		dev_err(&client->dev, "bad GPIO pin\n");
		return -EINVAL;
	}

	/*
	 * Pin 6 is configured by regs 0x00 and 0x01, pin 7 by 0x02 and
	 * 0x03, and so on.
	 */
	reg = pin * 2;

	ret = mma9551_write_config_byte(client, MMA9551_APPID_GPIO,
					reg, app_id);
	if (ret < 0) {
		dev_err(&client->dev, "error setting GPIO app_id\n");
		return ret;
	}

	ret = mma9551_write_config_byte(client, MMA9551_APPID_GPIO,
					reg + 1, bitnum);
	if (ret < 0) {
		dev_err(&client->dev, "error setting GPIO bit number\n");
		return ret;
	}

	switch (pin) {
	case mma9551_gpio6:
		reg = MMA9551_GPIO_POL_LSB;
		pol_mask = 1 << 6;
		break;
	case mma9551_gpio7:
		reg = MMA9551_GPIO_POL_LSB;
		pol_mask = 1 << 7;
		break;
	case mma9551_gpio8:
		reg = MMA9551_GPIO_POL_MSB;
		pol_mask = 1 << 0;
		break;
	case mma9551_gpio9:
		reg = MMA9551_GPIO_POL_MSB;
		pol_mask = 1 << 1;
		break;
	}
	pol_val = polarity ? pol_mask : 0;

	ret = mma9551_update_config_bits(client, MMA9551_APPID_GPIO, reg,
					 pol_mask, pol_val);
	if (ret < 0)
		dev_err(&client->dev, "error setting GPIO polarity\n");

	return ret;
}